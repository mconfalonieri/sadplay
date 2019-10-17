/*
 * sadplay - AdLib music player with graphics.
 * 
 * audio_output.h - abstract audio output interface.
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

#ifndef _SADPLAY_AUDIO_OUTPUT_H
#define _SADPLAY_AUDIO_OUTPUT_H

/**
 * Abstract class that defines the routines for the audio playback.
 */
class audio_output {
    public:
        /**
         * Destructor.
         */
        virtual ~audio_output() {}

        
        
};

#endif // _SADPLAY_AUDIO_OUTPUT_H