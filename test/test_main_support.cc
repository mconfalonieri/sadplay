/*
 * sadplay - AdLib music player with graphics.
 * 
 * test_main_support.cc - test file for main support functions.
 * 
 * Copyright (C) 2019 Marco Confalonieri <marco at marcoconfalonieri.it>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "main_support.h"

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include <unistd.h>

using std::string;

// Test list name
const char* TEST_LST = "test.lst";
// Test log name
const char* TEST_LOG = "test.log";
// Test command line arguments.
const char* TEST_CMDLINE_ARGV[] = {"./sadplay", "-v", "pippo.hsc", "pluto.hsc", "paperino.hsc"};
// Test command line arguments number.
const int TEST_CMDLINE_ARGC = 5;
// Test command line 2 arguments.
const char* TEST_CMDLINE2_ARGV[] = {"./sadplay", "-v", "-l", TEST_LOG, "-f", TEST_LST};
// Test command line 2 arguments number.
const int TEST_CMDLINE2_ARGC = 6;
// Test command line arguments.
const char* TEST_CMDLINE3_ARGV[] = {"./sadplay", "-v", "-f"};
// Test command line arguments number.
const int TEST_CMDLINE3_ARGC = 3;

// Index to the first file name
const int TEST_CMDLINE_INDEX = 2;

/**
 * Prepare an array with the test command line arguments.
 * 
 * @param   argc        argument number
 * @param   cargv       arguments
 * 
 * @return  the command line arguments.
 */
char** get_cmdline_argv(int argc, const char* cargv[]) {
    char** argv = new char*[argc];
    for (int i = 0; i < argc; i++) {
        argv[i] = new char[strlen(cargv[i])];
        strcpy(argv[i], cargv[i]);
    }
    return argv;
}

/**
 * Releases the resources for the array with the command line arguments.
 * 
 * @param   argv        the array to be freed
 */
void free_cmdline_argv(char* argv[]) {
    for (int i = 0; i < 5; i++) {
        delete argv[i];
    }
    delete argv;
}

/**
 * Prints the file list into a text file.
 * 
 * @param   out_file    the name of the output file
 */
void print_file_list(string out_file) {
    std::ofstream out_stream(out_file);
    for (int idx = TEST_CMDLINE_INDEX; idx < TEST_CMDLINE_ARGC; idx++) {
        out_stream << string(TEST_CMDLINE_ARGV[idx]) << std::endl;
    }
}

/**
 * Compares the file list in the sadplay_args argument provided with the list
 * available in the test data.
 * 
 * @param   args        the sadplay_args object to check
 *
 * @return  true if the comparison is successful
 */
bool check_file_list(sadplay_args& args) {
    bool test_ok = true;
    std::list<string>::const_iterator list_iterator = args.file_list.cbegin();
    for (int idx = TEST_CMDLINE_INDEX; idx < TEST_CMDLINE_ARGC; idx++) {
        string exp_result(TEST_CMDLINE_ARGV[idx]);
        string result = *list_iterator;
        if (exp_result != result) {
            test_ok = false;
            break;
        }
        list_iterator++;
    }
    return test_ok;
}

/**
 * Tests read_file_list_from_argv().
 * 
 * @return  true if the test is successful
 */
bool test_read_file_list_from_argv() {
    sadplay_args args;
    char** argv = get_cmdline_argv(TEST_CMDLINE_ARGC, TEST_CMDLINE_ARGV);
    int argc = TEST_CMDLINE_ARGC;
    int index = TEST_CMDLINE_INDEX;
    read_file_list_from_argv(&args, argc, argv, index);
    bool test_ok = check_file_list(args);
    free_cmdline_argv(argv);
    return test_ok;
}

/**
 * Tests read_file_list_from_file() with a file argument.
 *
 * @return  true if the test is successful
 */
bool test_read_file_list_from_file_1() {
    sadplay_args args;
    const char* out_file_name = TEST_LST;
    string out_file(out_file_name);
    print_file_list(out_file);
    read_file_list_from_file(&args, out_file);
    bool test_ok = check_file_list(args);
    remove(out_file_name);
    return test_ok;
}

/**
 * Tests read_file_list_from_file() with standard input.
 *
 * @return  true if the test is successful
 */
bool test_read_file_list_from_file_2() {
    sadplay_args args;
    const char* out_file_name = TEST_LST;
    string out_file(out_file_name);
    print_file_list(out_file);
    std::ifstream input(out_file_name);
    read_file_list_from_file(&args, string("-"), input);
    input.close();
    bool test_ok = check_file_list(args);
    remove(out_file_name);
    return test_ok;
}

bool test_read_command_line_1() {
    sadplay_args args;
    optind = 1;
    char** argv = get_cmdline_argv(TEST_CMDLINE_ARGC, TEST_CMDLINE_ARGV);
    int argc = TEST_CMDLINE_ARGC;
    read_command_line(&args, argc, argv);
    bool test_ok = args.verbose;
    if (test_ok) {
        test_ok = check_file_list(args);
    }
    return test_ok;
}

bool test_read_command_line_2() {
    sadplay_args args;
    optind = 1;
    const char* out_file_name = TEST_LST;
    string out_file(out_file_name);
    print_file_list(out_file);
    char** argv = get_cmdline_argv(TEST_CMDLINE2_ARGC, TEST_CMDLINE2_ARGV);
    int argc = TEST_CMDLINE2_ARGC;
    read_command_line(&args, argc, argv);
    bool test_ok = args.verbose && !args.log_file.empty();
    if (test_ok) {
        test_ok = check_file_list(args);
    }
    remove(out_file_name);
    return test_ok;
}

bool test_read_command_line_3() {
    sadplay_args args;
    optind = 1;
    char** argv = get_cmdline_argv(TEST_CMDLINE3_ARGC, TEST_CMDLINE3_ARGV);
    int argc = TEST_CMDLINE3_ARGC;
    read_command_line(&args, argc, argv);
    bool test_ok = args.verbose && args.file_list.empty() && args.error;
    return test_ok;
}

// Loads the tests in the appropriate array.
void load_test_map(std::map<std::string, bool(*)()>& tests) {
    tests["main_support|read_file_list_from_argv"] = test_read_file_list_from_argv;
    tests["main_support|read_file_list_from_file_1"] = test_read_file_list_from_file_1;
    tests["main_support|read_file_list_from_file_2"] = test_read_file_list_from_file_2;
    tests["main_support|read_command_line_1"] = test_read_command_line_1;
    tests["main_support|read_command_line_2"] = test_read_command_line_2;
    tests["main_support|read_command_line_3"] = test_read_command_line_3;
}
