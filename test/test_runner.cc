/*
 * sadplay - AdLib music player with graphics.
 * 
 * test_runner.cc - test runner.
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

#include <iostream>
#include <map>
#include <string>

using std::map;
using std::string;

typedef map<string, bool(*)()> test_map;
typedef test_map::const_iterator test_map_iterator;

/**
 * Loads the test map for the current suite.
 * 
 * @param   tests           the map with the loaded tests.
 */
extern void load_test_map(test_map &tests);

bool run_tests(test_map& tests) {
    bool result = true;
    for (
                test_map_iterator test_iterator = tests.cbegin();
                test_iterator != tests.cend();
                ++test_iterator
    ) {
        bool (*test_function)() = test_iterator->second;
        std::cout << " - " << test_iterator->first << ": ";
        bool test_result = test_function();
        if (!test_result) {
            result = false;
            std::cout << "FAILED." << std::endl;
        } else {
            std::cout << "OK." << std::endl;
        }
    }
    return result;
}

bool run_tests(test_map& tests, int argc, char* argv[]) {
    bool result = true;
    for (int idx = 1; idx < argc; idx++) {
        test_map_iterator test_iterator = tests.find(string(argv[idx]));
        if (test_iterator == tests.cend()) {
            result = false;
            std::cout << " - test " + string(argv[idx]) + " not found." << std::endl;
            break;
        }
        bool (*test_function)() = test_iterator->second;
        std::cout << " - " << test_iterator->first << ": ";
        bool test_result = test_function();
        if (!test_result) {
            result = false;
            std::cout << "FAILED." << std::endl;
        } else {
            std::cout << "OK." << std::endl;
        }
    }
    return result;
}

/**
 * Test runner main function.
 */
int main(int argc, char* argv[]) {
    test_map tests;
    load_test_map(tests);
    std::cout << "Running tests:" << std::endl;
    bool result = ((argc > 1)? run_tests(tests, argc, argv) : run_tests(tests));
    if (result) {
        std::cout << (result? "All tests ran smoothly." : "Errors found.")
                << std::endl;
    }
    return result? 0 : 1;
}
