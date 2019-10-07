#
# sadplay - AdLib music player with graphics.
# 
# Makefile.am - Automake configuration file.
# 
# Copyright (C) 2019 Marco Confalonieri <marco at marcoconfalonieri.it>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

# Automake options
AUTOMAKE_OPTIONS = subdir-objects
AM_CXXFLAGS = -Isrc

# Main sources
bin_PROGRAMS = sadplay
sadplay_SOURCES = src/main.cc src/main_support.cc src/sadplay.cc 

# Test sources
TESTS = test_main_support
check_PROGRAMS = test_main_support
test_main_support_SOURCES = test/test_runner.cc test/test_main_support.cc src/main_support.cc

# Other resources
README: README.md
