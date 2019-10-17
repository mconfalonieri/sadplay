/*
 * sadplay - AdLib music player with graphics.
 * 
 * adplug_player.cc - AdPlug player implementation.
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

#include "adplug_player.h"

#include <unistd.h>

#include "spectrum_analyzer.h"

using std::string;

#ifndef min
#  define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

// Constructor. It initializes the audio data.
adplug_player::adplug_player(const string& filename) : opl(CEmuopl(spectrum_analyzer::SAMPLING_RATE, true, true)) {
    opl.init();
    player = CAdPlug::factory(filename, &opl);
    ended = (player == NULL);
}

// Destructor
adplug_player::~adplug_player() {
}

int adplug_player::fill_buffer(void* audiobuf, int len, unsigned char sample_size) {
    static long minicnt = 0;
    long i, towrite = len / sample_size;
    char* pos = (char*) audiobuf;

    // Prepare audiobuf with emulator output
    while (towrite > 0) {
        while (minicnt < 0) {
            minicnt += spectrum_analyzer::SAMPLING_RATE;
            ended = !player->update();
        }
        i = min(towrite, (long)(minicnt / player->getrefresh() + 4) & ~3);
        opl.update((short *)pos, i);
        pos += i * sample_size; towrite -= i;
        minicnt -= (long)(player->getrefresh() * i);
    }
}