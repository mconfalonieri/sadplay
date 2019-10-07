/*
 * sadplay - AdLib music player with graphics.
 * 
 * sadplay.h - application class header
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

#ifndef _SADPLAY_SADPLAY_H_
#define _SADPLAY_SADPLAY_H_

#include <fstream>
#include <list>
#include <map>
#include <string>

#include "display.h"

/**
 * Command line arguments unrolled.
 */
struct sadplay_args {
    /**
     * Verbose output.
     */
    bool verbose;

    /**
     * Log file.
     */
    std::string log_file;

    /**
     * Audio file list.
     */
    std::list<std::string> file_list;
};

/**
 * Main application class.
 */
class sadplay {
    public:
        /**
         * Constructor. It initializes the display drivers map with all the
         * known display drivers.
         */
        sadplay();

        /**
         * Destructor.
         */
        ~sadplay();
        
        /**
         * Runs the application.
         * 
         * @param   args        the parsed command line arguments
         * 
         * @return  the exit code for the program.
         */
        int run(sadplay_args* args);

    protected:
        /**
         * Prints a log line. It prints a line in the log, and eventually on
         * the screen, taking into account the verbose flag.
         * 
         * @param   line        line to be printed.
         */
        void log(std::string line);

    private:
        /**
         * Display drivers.
         */
        std::map<std::string, display_factory*> drivers;

        /**
         * Verbose flag.
         */
        bool verbose;

        /**
         * Log file.
         */
        std::ofstream log_stream;
};

#endif // _SADPLAY_SADPLAY_H_