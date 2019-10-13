/*
 * sadplay - AdLib music player with graphics.
 * 
 * sdl_driver.cc - Implementation for SDL display driver.
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

#include "sdl_driver.h"

// Implementation of the callback.
extern "C" int sdl_channel_bar_callback(Uint32 time_elapsed, void* param) {

}

/**
 * SDL display driver.
 */
class sdl_display_driver : public display {
    public:
        /**
         * Initializes the view.
         */
        void initialize();

        /**
         * Updates the channel bar.
         */
        void update_channel_bar();

        /**
         * Returns the channel bar instance.
         */
        channel_bar* get_channel_bar();
    
    private:
};

void update_channel_bar_decay();