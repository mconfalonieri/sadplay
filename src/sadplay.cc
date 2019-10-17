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
#include "frequency_bar.h"

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
    const int NUM_CHANNELS = frequency_bar::CHANNEL_BARS;

    // Sets the verbose flag.
    this->verbose = args->verbose;

    log("Initialize window");
    driver->initialize(NUM_CHANNELS);

    log("Preparing player");
    adplug_player* player = NULL;
 
    log("Entering main cycle");
    main_cycle(args, player);
    
    log("Exiting.");
    delete player;
    return 0;
}

void sadplay::main_cycle(sadplay_args* args, adplug_player* player) {
    const std::list<string>::const_iterator BEGIN = args->file_list.cbegin();
    const std::list<string>::const_iterator END = args->file_list.cend();

    std::list<string>::const_iterator ptr = BEGIN;
    int cmd = CMD_NEXT;

    while (ptr != END && cmd != CMD_QUIT) {
        log("Playing file: " + *ptr);
        cmd = CMD_NONE;
        delete player;
        player = new adplug_player(*ptr);
        if (!driver->play(player)) continue;
        bool paused = false;
        while (!cmd) {
            cmd = handle_events(player);
            switch (cmd) {
                case CMD_PREV:
                    log("Issued command CMD_PREV");
                    if (args->repeat && ptr == BEGIN) ptr = END;
                    if (ptr != BEGIN) --ptr;
                    break;
                case CMD_NEXT:
                    log("Issued command CMD_NEXT");
                    if (ptr != END) ++ptr;
                    break;
                case CMD_QUIT:
                    log("Issued command CMD_QUIT");
                    ptr = END;
                    break;
                case CMD_PAUSE:
                    log("Issued command CMD_PAUSE");
                    if (paused) driver->cont();
                    else driver->pause();
                    paused = !paused;
                    cmd = CMD_NONE;
                    break;
            }
        }
        log("Stopping the music.");
        driver->stop();

        if (args->repeat && ptr == END) {
            ptr = BEGIN;
        }
    }
}
int sadplay::handle_events(adplug_player* player) {
    int cmd = CMD_NONE;
    bool valid_cmd = false;
    while (!cmd) {
        SDL_Event e;
        SDL_PollEvent(&e);
        switch (e.type) {
            case SDL_QUIT:
                cmd = CMD_QUIT;
                break;
            case SDL_KEYUP:
                cmd = handle_keyboard_event(e);
                break;               
            default:
                cmd = CMD_NONE;
        }
        if (player->is_ended()) {
            cmd = CMD_NEXT;
        }
    }
    return cmd;
}

int sadplay::handle_keyboard_event(SDL_Event& e) {
    int cmd;
    switch (e.key.keysym.sym) {
        case SDLK_RIGHT:
        case SDLK_n:
        case SDLK_DOWN:
            cmd = CMD_NEXT;
            break;
        case SDLK_LEFT:
        case SDLK_UP:
            cmd = CMD_PREV;
            break;
        case SDLK_q:
            cmd = CMD_QUIT;
            break;
        case SDLK_SPACE:
            cmd = CMD_PAUSE;
            break;
        default:
            cmd = CMD_NONE;
    }
    return cmd;
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

