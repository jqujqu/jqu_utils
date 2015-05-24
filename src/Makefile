# This file is part of the jqu_utils
#
# Copyright (C) 2010-2014 University of Southern California and
# Andrew D. Smith
#
# Authors: Jenny Qu
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#

ifndef SMITHLAB_CPP
SMITHLAB_CPP=$(realpath smithlab_cpp)
endif

PROGS = bedseparate
CXX = g++
CXXFLAGS = -Wall -fmessage-length=50
OPTFLAGS = -O2 
DEBUGFLAGS = -g
LIBS = -lgsl -lgslcblas

ifdef DEBUG
CXXFLAGS += $(DEBUGFLAGS)
endif

ifdef OPT
CXXFLAGS += $(OPTFLAGS)
endif

INCLUDEDIRS = $(SMITHLAB_CPP) 
INCLUDEARGS = $(addprefix -I,$(INCLUDEDIRS))


# Flags for Mavericks
ifeq "$(shell uname)" "Darwin"
CXXFLAGS += -arch x86_64
INCLUDEARGS += -I/usr/local/include
LIBS += -L/usr/local/lib
ifeq "$(shell if [ `sysctl -n kern.osrelease | cut -d . -f 1` -ge 13 ];\
              then echo 'true'; fi)" "true"
CXXFLAGS += -stdlib=libstdc++
endif
endif

all: $(PROGS)

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) $(INCLUDEARGS) -c -o $@ $< 

%: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDEARGS) -o $@ $^ $(LIBS)

$(PROGS): $(addprefix $(SMITHLAB_CPP)/, GenomicRegion.o smithlab_os.o \
	smithlab_utils.o OptionParser.o)  


install: all
	@mkdir -p ../bin
	@install -m 755 $(PROGS) ../bin

clean:
	@-rm -f $(PROGS) *.o *.so *.a *~

.PHONY: clean
