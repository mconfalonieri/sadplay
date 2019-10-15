/*
 * sadplay - AdLib music player with graphics.
 * 
 * display.h - abstract display interface.
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

#ifndef _SADPLAY_DISPLAY_H_
#define _SADPLAY_DISPLAY_H_

#include "channel_bar.h"

/**
 * The display class represents an abstract view for the application.
 */
class display {
    public:
        /**
         * Initializes the view.
         * 
         * @param   num_channels    number of channels
         *
         * @return  true if correctly initialized
         */
        virtual bool initialize(int num_channels) = 0;

        /**
         * Updates the channel bar.
         */
        virtual void update_channel_bar() = 0;

        /**
         * Returns the channel bar instance.
         * 
         * @return  the channel bar
         */
        virtual channel_bar* get_channel_bar() = 0;

};

#endif // _SADPLAY_DISPLAY_H_
