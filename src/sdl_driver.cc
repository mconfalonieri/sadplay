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
    sdl_display_driver* driver = (sdl_display_driver*) param;
    driver->update_channel_bar_decay(time_elapsed);
    return 1;
}

// Constructor.
sdl_display_driver::sdl_display_driver(): mutex(NULL), timer_id(0) {

}

// Destructor.
sdl_display_driver::~sdl_display_driver() {
    if (timer_id != 0) {
        SDL_RemoveTimer(timer_id);
    }
}

        /**
         * Initializes the view.
         */
        void sdl_display_driver::initialize();

        /**
         * Updates the channel bar.
         */
        void sdl_display_driver::update_channel_bar();

        /**
         * Returns the channel bar instance.
         */
        channel_bar* sdl_display_driver::get_channel_bar();

    protected:
        /**
         * Updates the channel bar. It is called by the callback.
         */
        void sdl_display_driver::update_channel_bar_decay(Uint32 time_elapsed);
    
