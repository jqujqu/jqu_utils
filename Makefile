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
UTILS_ROOT = $(shell pwd)
BINDIR = $(UTILS_ROOT)/bin

export SMITHLAB_CPP := $(shell pwd)/src/smithlab_cpp

all:
	@make -C src UTILS_ROOT=$(UTILS_ROOT) OPT=1
install:
	@make -C src UTILS_ROOT=$(UTILS_ROOT) OPT=1 install
clean:
	@make -C src UTILS_ROOT=$(UTILS_ROOT) clean
.PHONY: clean



