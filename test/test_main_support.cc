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

#include <iostream>
#include <list>
#include <string>
#include <string.h>

using std::string;

/**
 * Tests read_file_list_from_argv().
 * 
 * @return              true if the test is successful
 */
bool test_read_file_list_from_argv() {
    sadplay_args args;
    char* argv[5];
    const char* cmdline[] = {"./sadplay", "-v", "pippo.hsc", "pluto.hsc", "paperino.hsc"};
    for (int i = 0; i < 5; i++) {
        argv[i] = (char *) malloc(strlen(cmdline[i]));
        strcpy(argv[i], cmdline[i]);
    }
    int argc = 5;
    int index = 2;
    read_file_list_from_argv(&args, argc, argv, index);
    bool test_ok = true;
    std::list<string>::const_iterator list_iterator = args.file_list.cbegin();
    for (int idx = index; idx < argc; idx++) {
        string exp_result((const char*) argv[idx]);
        string result = *list_iterator;
        if (exp_result != result) {
            std::cout << "expected \"" << exp_result << "\"; obtained \"" << result << "\"." << std::endl;
            test_ok = false;
            break;
        }
    }
    for (int i = 0; i < 5; i++) {
        free(argv[i]);
    }
    return test_ok;
}
// Loads the tests in the appropriate array.
void load_test_map(std::map<std::string, bool(*)()>& tests) {
    tests["test_read_file_list_from_argv"] = test_read_file_list_from_argv;
}
