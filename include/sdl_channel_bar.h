/*
 * sadplay - AdLib music player with graphics.
 * 
 * sdl_channel_bar.h - header for SDL channel bar.
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
#ifndef _SADPLAY_SDL_CHANNEL_BAR_H_
#define _SADPLAY_SDL_CHANNEL_BAR_H_

#include <vector>
#include <SDL.h>
#include "channel_bar.h"

#ifdef SADPLAY_TEST
// Forward declaration of the accessor class used for tests.
class sdl_channel_bar_test_access;
#endif // SADPLAY_TEST

/**
 * SDL channel bar. It uses SDL concurrency routines and callback mechanisms.
 */
class sdl_channel_bar : public channel_bar {
    public:
        /**
         * Milliseconds that the bar will last from 100% to 0.
         */
        static const int DECAY_TIMER = 2000;

        /**
         * Channel bar constructor. It builds a new instance of the SDL
         * channel bar with the given number of channels.
         * 
         * @param   num_channels        number of channels
         */
        sdl_channel_bar(int num_channels);

        /**
         * Destructor.
         */
        virtual ~sdl_channel_bar();

        /**
         * Updates a channel.
         * 
         * @param   channel     the channel that needs to be updated
         * @param   value       the new value for the channel
         */
        void update(int channel, int value);

        /**
         * Updates all channels.
         * 
         * @param   values    the values for the channels
         */
        void update_all(const int values[]);

        /**
         * Sets all the channel values to zero.
         */
        void reset_channels();

        /**
         * Lowers the channel bar according to the time elapsed.
         * 
         * @param   time_elapsed        time elapsed since last update in
         *                              milliseconds
         */
        void time_elapsed(Uint32 time_elapsed);

        /**
         * Returns the number of channels.
         * 
         * @return  the number of channels
         */
        int get_numchannels();

        /**
         * Returns the channel.
         * 
         * @param  channels             an array sized to contain the channel
         *                              values
         */
        void get_channels(int* channels);

    private:
#ifdef SADPLAY_TEST
        /// Provide access to test class
        friend class sdl_channel_bar_test_access;
#endif // SADPLAY_TEST

        /**
         * Mutex used to synchronize the operations on the channel bar.
         */
        SDL_mutex* mutex;

        /**
         * The channels in the channel bar.
         */
        std::vector<int> channels;
};

#endif // _SADPLAY_SDL_CHANNEL_BAR_H_