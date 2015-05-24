/*    bedseparate: separate bed-A into multiple files according to 
 *    bed intervals in bed-B    
 *
 *    Copyright (C) 2014 Jenny Qu
 *
 *    Authors: Jenny Qu
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "OptionParser.hpp"
#include "smithlab_utils.hpp"
#include "smithlab_os.hpp"
#include "GenomicRegion.hpp"

using std::string;
using std::vector;
using std::endl;
using std::cerr;

int
main(int argc, const char **argv) {

  try {

    /* FILES */
    string outfile;
    bool VERBOSE = false;

    /****************** GET COMMAND LINE ARGUMENTS ***************************/
    OptionParser opt_parse(strip_path(argv[0]), "", "<BED-A> <BED-B>");
    opt_parse.add_opt("verbose", 'v', "print more run info",
                      false , VERBOSE);
    vector<string> leftover_args;
    opt_parse.parse(argc, argv, leftover_args);
    if (argc == 1 || opt_parse.help_requested()) {
      cerr << opt_parse.help_message() << endl;
      return EXIT_SUCCESS;
    }
    if (opt_parse.about_requested()) {
      cerr << opt_parse.about_message() << endl;
      return EXIT_SUCCESS;
    }
    if (opt_parse.option_missing()) {
      cerr << opt_parse.option_missing_message() << endl;
      return EXIT_SUCCESS;
    }
    if (leftover_args.size() < 2) {
      cerr << opt_parse.help_message() << endl;
      return EXIT_SUCCESS;
    }
    const string bedAfile(leftover_args[0]);
    const string bedBfile(leftover_args[1]);
    /**********************************************************************/

    vector<GenomicRegion> intervalsA;
    ReadBEDFile(bedAfile, intervalsA);
    assert(check_sorted(intervalsA));
    if (!check_sorted(intervalsA))
      throw SMITHLABException("regions not sorted in file: " + bedAfile);

    vector<GenomicRegion> intervalsB;
    ReadBEDFile(bedBfile, intervalsB);
    assert(check_sorted(intervalsB));
    if (!check_sorted(intervalsB))
      throw SMITHLABException("regions not sorted in file: " + bedBfile);

    vector<GenomicRegion>::iterator iterA = intervalsA.begin();
    for(size_t i = 0; i < intervalsB.size(); ++i){
      string outfile = bedAfile + intervalsB[i].get_name(); 
      std::ofstream of;
      of.open(outfile.c_str(), std::ios::app);
      std::ostream out(of.rdbuf());
      
      while ( (*iterA).get_chrom() < intervalsB[i].get_chrom() ||
               (*iterA).get_end() < intervalsB[i].get_start() ) 
        ++iterA;
      if (*iterA < intervalsB[i] ){
        GenomicRegion interval(intervalsB[i].get_chrom(),
                               intervalsB[i].get_start(),
                               (*iterA).get_end());
        interval.set_name((*iterA).get_name());
        interval.set_score((*iterA).get_score());
        out << interval << '\n'; 
        ++iterA;
      }
      while((*iterA).get_chrom() == intervalsB[i].get_chrom() &&
            (*iterA).get_end() < intervalsB[i].get_end()){
        out << *iterA << '\n';
        ++iterA;
      }
      if (intervalsB[i].get_end() > (*iterA).get_start()){
        GenomicRegion interval(intervalsB[i].get_chrom(),
                               (*iterA).get_start(),
                               intervalsB[i].get_end());
        interval.set_name((*iterA).get_name());
        interval.set_score((*iterA).get_score());
        out << interval << '\n'; 
      }
      of.close();      
    }

  }
  catch (SMITHLABException &e) {
    cerr << "ERROR:\t" << e.what() << endl;
    return EXIT_FAILURE;
  }
  catch (std::bad_alloc &ba) {
    cerr << "ERROR: could not allocate memory" << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
