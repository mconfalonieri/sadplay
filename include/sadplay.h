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

#include "sdl_driver.h"

/**
 * Command line arguments unrolled.
 */
struct sadplay_args {
    /**
     * Constructor.
     */
    sadplay_args();

    /**
     * Log file.
     */
    std::string log_file;

    /**
     * Audio file list.
     */
    std::vector<std::string> file_list;

    /**
     * Verbose output.
     */
    bool verbose;

     /**
     * Command line parsing error.
     */
    bool error;

    /**
     * Repeat queue.
     */
    bool repeat;

    /**
     * Plays one song continuosly.
     */
    bool continuous;
    
    /**
     * Shuffle playlist.
     */
    bool shuffle;
};

/**
 * Main application class.
 */
class sadplay {
    public:
        /**
         * Default display driver name.
         */
        static const std::string DEFAULT_DRIVER_NAME;

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
        void main_cycle(sadplay_args* args, adplug_player* player);
        
        /**
         * Prints a log line. It prints a line in the log, and eventually on
         * the screen, taking into account the verbose flag.
         * 
         * @param   line        line to be printed.
         */
        void log(std::string line);

        /**
         * Handles the SDL events. It also determines if the song has ended,
         * pushing a CMD_NEXT in case.
         * 
         * @param   player      the player
         * 
         * @return  command issued.
         */
        int handle_events(adplug_player* player);

        /**
         * Handles the keyboard events. If an unsupported key is pressed, it
         * returns CMD_NONE.
         * 
         * @param   e           event that should be decoded.
         *
         * @return  the corresponding command.
         */
        int handle_keyboard_event(SDL_Event& e);

        /**
         * Shows the text on screen.
         * 
         * @param   text        the text that should be shown.
         */
        void show_text(const char* text);

        /**
         * Shuffle playlist.
         * 
         * @param   playlist    reference to the playlist vector
         */
        void shuffle(std::vector<std::string> &playlist);

    private:
        /**
         * Verbose flag.
         */
        bool verbose;

        /**
         * Log file.
         */
        std::ofstream log_stream;

        /**
         * Display driver.
         */
        sdl_display_driver* driver;

        /**
         * The seed for the random engine.
         */
        unsigned random_seed;

        /**
         * Quit command.
         */
        const static int CMD_QUIT = -1;

        /**
         * No command.
         */
        const static int CMD_NONE = 0;
        /**
         * Next song command.
         */
        const static int CMD_NEXT = 1;

        /**
         * Previous song command.
         */
        const static int CMD_PREV = 2;

        /**
         * Pause / continue.
         */
        const static int CMD_PAUSE = 3;

        /**
         * Info command.
         */
        const static int CMD_INFO = 4;
};

#endif // _SADPLAY_SADPLAY_H_