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

#include <vector>

/**
 * The channel_bar class represents the channel bar that should hold the
 * channel activity values.
 */
class channel_bar {
    public:
        /**
         * Gives access to a channel for reading or writing.
         * 
         * @param   channel     the channel that needs to be accessed
         * 
         * @return  the reference to the channel
         */
        virtual int& operator[](int channel) = 0;
};

/**
 * The display class represents an abstract view for the application.
 */
class display {
    public:
        /**
         * Initializes the view.
         */
        virtual void initialize() = 0;

        /**
         * Updates the channel bar.
         */
        virtual void update_channel_bar(channel_bar* channel_bar) = 0;
};

/**
 * The display_factory is used to create instances of display adapters.
 */
class display_factory {
    public:
        /**
         * Creates a new display instance.
         */ 
        virtual display* new_instance() = 0;

        /**
         * Returns the name of the driver.
         */
        virtual std::string name() = 0; 
};
