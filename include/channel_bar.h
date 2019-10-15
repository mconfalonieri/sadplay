/*
 * sadplay - AdLib music player with graphics.
 * 
 * channel_bar.h - abstract channel bar interface.
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

#ifndef _SADPLAY_CHANNEL_BAR_H_
#define _SADPLAY_CHANNEL_BAR_H_

/**
 * The channel_bar class represents the channel bar that should hold the
 * channel activity values.
 */
class channel_bar {
    public:
        /**
         * Updates a channel.
         * 
         * @param   channel     the channel that needs to be updated
         * @param   value       the new value for the channel
         */
        virtual void update(int channel, int value) = 0;

        /**
         * Updates all channels.
         * 
         * @param   values    the values for the channels
         */
        virtual void update_all(const int values[]) = 0;

        /**
         * Sets all the channel values to zero.
         */
        virtual void reset_channels() = 0;

        /**
         * Returns the number of channels.
         * 
         * @return  the number of channels
         */
        virtual int get_numchannels() = 0;
};

#endif // _SADPLAY_CHANNEL_BAR_H_
