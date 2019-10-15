/*
 * sadplay - AdLib music player with graphics.
 * 
 * sadplay.cc - application class implementation
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
#include "sadplay.h"

#include <iostream>

#include "sdl_driver.h"

using std::string;
using std::map;

// Assigning the constant value
const string sadplay::DEFAULT_DRIVER_NAME = "sdl";

// Constructor.
sadplay::sadplay(): verbose(false), log_stream(), driver(NULL) {
    this->driver = new sdl_display_driver();
}

// Destructor.
sadplay::~sadplay() {
    if (this->log_stream.is_open()) {
        this->log_stream.close();
    }
    delete this->driver;
}

// Application runner.
int sadplay::run(sadplay_args* args) {
    // Sets the verbose flag.
    this->verbose = args->verbose;
    log("Initialize window");
    driver->initialize(8);
    channel_bar* bar = driver->get_channel_bar();
    log("Preparing channel bar");
    for (int c = 0; c < 8; c++) {
        bar->update(c, 100);
    }
    log("Updating channel bar");
    driver->update_channel_bar();
    int quit = 0;
    SDL_Event e;
    log("Wait for command");
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = -1;
            }
        }
    }
    return 0;
}

// Logger.
void sadplay::log(string line) {
    // Log to stdout if verbose (-v) flag present.
    if (this->verbose) {
        std::cout << line << std::endl;
    }
    // Log to file if logfile (-l <logfile>) option is present.
    if (this->log_stream.is_open()) {
        this->log_stream << line << std::endl;
    }
}

