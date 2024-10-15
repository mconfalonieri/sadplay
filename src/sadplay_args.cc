/*
 * sadplay - AdLib music player with graphics.
 * 
 * sadplay_args.cc - command line arguments class implementation
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
#include "sadplay_args.h"
#include <ctime>

// Constructor
sadplay_args::sadplay_args() : verbose(false), error(false), repeat(false),
        continuous(false), shuffle(false) {
            time_t now;
            time(&now);
            srand48(now);
}
