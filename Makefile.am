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

# Main sources
bin_PROGRAMS = sadplay
sadplay_SOURCES = src/frequency_bar.cc src/main.cc src/main_support.cc \
	src/sadplay.cc src/sdl_channel_bar.cc src/sdl_driver.cc \
	src/spectrum_analyzer.cc src/adplug_player.cc \
	include/channel_bar.h include/display.h include/frequency_bar.h \
	include/main_support.h include/sadplay.h include/sdl_channel_bar.h \
	include/sdl_driver.h include/spectrum_analyzer.h

# Test cases
TESTS = $(check_PROGRAMS)

# Test programs
check_PROGRAMS = test_main_support test_sdl_channel_bar

test_main_support_LIBS = $(CODE_COVERAGE_LIBS)
test_main_support_CXXFLAGS = $(CODE_COVERAGE_CXXFLAGS) -DSADPLAY_TEST
test_main_support_SOURCES = test/test_runner.cc test/test_main_support.cc \
	src/main_support.cc include/main_support.h

test_sdl_channel_bar_LIBS = $(CODE_COVERAGE_LIBS)
test_sdl_channel_bar_CXXFLAGS = $(CODE_COVERAGE_CXXFLAGS) -DSADPLAY_TEST
test_sdl_channel_bar_SOURCES = test/test_runner.cc \
	test/test_sdl_channel_bar.cc src/sdl_channel_bar.cc \
	include/sdl_channel_bar.h

# Other resources
README: README.md

# lcov report
if CODE_COVERAGE_ENABLED
cov-reset:
	@rm -fr coverage
	@find . -name "*.gcda" -exec rm {} \;
	@lcov --directory . --zerocounters

cov-report:
	@mkdir -p coverage
	@lcov --compat-libtool --no-external --directory src --capture --output-file coverage/app.info  
	@genhtml -o docs/coverage/ coverage/app.info 

cov:
	@make cov-report

clean-local:
	@make cov-reset 

check:
	@make cov

endif 