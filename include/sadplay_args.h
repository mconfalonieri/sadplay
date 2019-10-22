/*
 * sadplay - AdLib music player with graphics.
 * 
 * sadplay_args.h - command line arguments class header
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

#ifndef _SADPLAY_SADPLAY_ARGS_H_
#define _SADPLAY_SADPLAY_ARGS_H_

#include <string>
#include <vector>


// TODO: moving sadplay_args in its own file.
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

#endif // _SADPLAY_SADPLAY_ARGS_H_