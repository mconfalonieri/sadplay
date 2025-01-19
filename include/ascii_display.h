/*
 * sadplay - AdLib music player with graphics.
 * 
 * ascii_display.h - ASCII display interface.
 * 
 * Copyright (C) 2025 Marco Confalonieri <marco at marcoconfalonieri.it>
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

#ifndef _SADPLAY_ASCII_DISPLAY_H_
#define _SADPLAY_ASCII_DISPLAY_H_

#include "display.h"

/**
 * The display class represents an abstract view for the application.
 */
class ascii_display: public display {
    public:
        /**
         * Constructor.
         */
        ascii_display();

        /**
         * Destructor.
         */
        ~ascii_display();

        /**
         * Initializes the view.
         *
         * @return  true if correctly initialized
         */
        bool initialize();

        /**
         * Updates the channel bar.
         */
        void update_channel_bar();

        /**
         * Returns the channel bar instance.
         * 
         * @return  the channel bar
         */
        channel_bar* get_channel_bar();

        /**
         * Returns the maximum number of supported channels.
         * 
         * @return the number of supported channels
         */
        int get_max_channels();
    
    private:
        /**
         * Number of channels.
         */
        static const int ONE_CHANNEL;

        /**
         * Frequency limits
         */
        static const double FREQ_LIMIT[];
};

#endif // _SADPLAY_ASCII_DISPLAY_H_
