/*
 * sadplay - AdLib music player with graphics.
 * 
 * main.cc - entry point.
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
#include <string>

#include <unistd.h>

#include "main_support.h"
#include "sadplay.h"

// The VERSION macro should be already defined.
#ifndef VERSION
#define VERSION "<unspecified>"
#endif

/**
 * GPLv3 license text that is displayed at start.
 */
const std::string SADPLAY_LICENSE =
    "sadplay version " VERSION " - Copyright (C) 2019 Marco Confalonieri\n\n"
    "This program comes with ABSOLUTELY NO WARRANTY; for details type `W'.\n"
    "This is free software, and you are welcome to redistribute it under\n"
    "certain conditions; type `C' for details.\n";

/**
 * Main function. It prints the license message and starts up the application
 * loop.
 * 
 * @param   argc        number of command line arguments
 * @param   argv        array of command line arguments
 *
 * @return  0 if the application exits normally. Any different value means
 *          that there was a problem.
 */
int main(int argc, char* argv[]) {

    // The app arguments.
    sadplay_args args;

    // Prints the standard license
    std::cout << SADPLAY_LICENSE << std::endl;

    read_command_line(&args, argc, argv);

    // The app main class.
    sadplay app;
    app.run(&args);

    return 0;
}
