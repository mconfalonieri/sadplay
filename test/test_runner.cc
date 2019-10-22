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
    std::cout << "1.." << tests.size() << std::endl;
    int i = 0;
    for (
                test_map_iterator test_iterator = tests.cbegin();
                test_iterator != tests.cend();
                ++test_iterator
    ) {
        time_t start, end;
        bool (*test_function)() = test_iterator->second;
        time(&start);
        bool test_result = test_function();
        time(&end);
        if (!test_result) {
            result = false;
            std::cout << "not ok ";
        } else {
            std::cout << "ok ";
        }
        std::cout << ++i << " ";
        std::cout << "- " << test_iterator->first << " # time=" << (end - start) << "ms" << std::endl;
    }
    return result;
}

/**
 * Test runner main function.
 */
int main(int argc, char* argv[]) {
    test_map tests;
    load_test_map(tests);
    bool result = run_tests(tests);
    return result? 0 : 1;
}
