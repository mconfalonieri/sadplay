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

#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <iostream>

#include "sdl_driver.h"
#include "frequency_bar.h"
#include "texts.h"

using std::string;
using std::map;

// Assigning the constant value
const string sadplay::DEFAULT_DRIVER_NAME = "sdl";

// Constructor.
sadplay::sadplay(): verbose(false), log_stream(), driver(NULL) {
    this->driver = new sdl_display_driver();
    random_seed = std::chrono::system_clock::now().time_since_epoch().count();
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

    if (args->error) {
        show_text(texts::CMDLINE_HELP_TEXT);
        return 1;
    }

    // Sets the verbose flag.
    this->verbose = args->verbose;

    log("Initialize window");
    driver->initialize(NUM_CHANNELS);

    log("Preparing player");
    adplug_player* player = NULL;
 
    // Shuffles the playlist, if required.
    if (args->shuffle) shuffle(args->file_list);
    log("Entering main cycle");
    main_cycle(args, player);
    
    log("Exiting.");
    delete player;
    player = NULL;
    
    return 0;
}

void sadplay::main_cycle(sadplay_args* args, adplug_player* player) {
    const std::vector<string>::const_iterator BEGIN = args->file_list.cbegin();
    const std::vector<string>::const_iterator END = args->file_list.cend();

    std::vector<string>::const_iterator ptr = BEGIN;
    int cmd = CMD_NEXT;

    while (ptr != END && cmd != CMD_QUIT) {
        string msg = "Playing: " + (*ptr) + "\n";
        show_text(msg.c_str());

        cmd = CMD_NONE;
        delete player;
        player = new adplug_player(*ptr, args->continuous);
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
                case CMD_INFO:
                    string msg = "Playing: " + (*ptr) + "\n";
                    show_text(msg.c_str());
                    cmd = CMD_NONE;
            }
            driver->render();
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
    SDL_Event e;
    SDL_PollEvent(&e);
    switch (e.type) {
        case SDL_QUIT:
            cmd = CMD_QUIT;
            break;
        case SDL_KEYDOWN:
            if (e.key.repeat == 0)
                cmd = handle_keyboard_event(e);
            break;               
        default:
            cmd = CMD_NONE;
    }

    if (player->is_ended()) cmd = CMD_NEXT;
    
    return cmd;
}

int sadplay::handle_keyboard_event(SDL_Event& e) {
    int cmd = CMD_NONE;
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
        case SDLK_h:
            show_text(texts::HELP_TEXT);
            break;
        case SDLK_w:
            show_text(texts::WARRANTY_TEXT);
            break;
        case SDLK_c:
            show_text(texts::LICENSE_TEXT);
            break;
        case SDLK_i:
            cmd = CMD_INFO;
    }
    return cmd;
}

// Shows informational text
void sadplay::show_text(const char* text) {
    std::cerr << text << std::endl;
}

// Shuffles the playlist. Using the STL-provided function and convincing
// the compiler to use it would have created different compilations options to
// e used on different systems, most notably MacOS X.
void sadplay::shuffle(std::vector<string> &playlist) {
    int size = playlist.size();
    std::vector<string> original_playlist(playlist);
    std::map<long, int> refs;
    std::vector<long> positions(size);
    for (int i = 0; i < size; i++) {
        long rnd = lrand48();
        positions[i] = rnd;
        refs[rnd] = i;
    }
    std::sort(positions.begin(), positions.end());
    for (int i = 0; i < size; i++) {
        int newpos = refs[positions[i]];
        playlist[newpos] = original_playlist[i];
    }
    return;
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

