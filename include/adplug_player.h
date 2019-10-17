/*
 * sadplay - AdLib music player with graphics.
 * 
 * adplug_player.h - AdPlug player interface.
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

#ifndef _SADPLAY_ADPLUG_PLAYER_H_
#define _SADPLAY_ADPLUG_PLAYER_H_

#include <string>

#include <adplug/adplug.h>

/**
 * AdPlug player.
 */
class adplug_player {
    public:
        /**
         * Constructor.
         */
        adplug_player(const std::string& filename);

        /**
         * Destructor.
         */
        ~adplug_player();

        /**
         * Fills an audio buffer with the given amount of samples.
         * 
         * @param   audiobuf        audio buffer
         * @param   len             buffer size
         * @param   sample_size     sample size
         * 
         * @return  milliseconds to next call
         */
        void fill_buffer(void* audiobuf, int len, unsigned char sample_size);

        bool is_ended() { return ended; }

    private:
        /**
         * OPL chip or emulator.
         */
        Copl* opl;

        /**
         * Player.
         */
        CPlayer* player;

        /**
         * Audio buffer.
         */
        short* audiobuf;

        /**
         * Defines if the playback has ended.
         */
        bool ended;
};

#endif // _SADPLAY_ADPLUG_PLAYER_H_