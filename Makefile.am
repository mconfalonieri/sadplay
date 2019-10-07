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
