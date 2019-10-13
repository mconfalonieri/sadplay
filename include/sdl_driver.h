/*
 * sadplay - AdLib music player with graphics.
 * 
 * sdl_driver.h - header for SDL display driver.
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
#ifndef _SADPLAY_SDL_DRIVER_H_
#define _SADPLAY_SDL_DRIVER_H_


#include <vector>

#include <SDL.h>

#include "display.h"

/**
 * Function that must be called by the SDL timer to update the channel bar.
 * 
 * @param   time_elapsed        time elapsed since last update in milliseconds
 * @param   param               the channel bar that needs to be updated
 * 
 * @return  if 0 is returned, the timer is cancelled.
 */
extern "C" int sdl_channel_bar_callback(Uint32 time_elapsed, void* param);

/**
 * SDL display driver.
 */
class sdl_display_driver : public display {
    public:
        /**
         * Constructor.
         */
        sdl_display_driver();

        /**
         * Destructor.
         */
        ~sdl_display_driver();

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

    protected:
        /**
         * Updates the channel bar. It is called by the callback.
         */
        void update_channel_bar_decay();
    
    private:

        // Declares the function as friend.
        friend int sdl_channel_bar_callback(Uint32 time_elapsed, void* param);

        /**
         * Mutex.
         */
        SDL_mutex* mutex;

};

#endif // _SADPLAY_SDL_DRIVER_H_