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

#include <iostream>

#include <adplug/temuopl.h>
#include <unistd.h>

#include "spectrum_analyzer.h"

using std::string;

#ifndef min
#  define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

// Constructor. It initializes the audio data.
adplug_player::adplug_player(const string& filename, bool continuous) :
        opl(NULL), continuous(continuous) {
    Copl* opl1 = new CTemuopl(spectrum_analyzer::SAMPLING_RATE, true, false);
    Copl* opl2 = new CTemuopl(spectrum_analyzer::SAMPLING_RATE, true, false);
#ifdef HAVE_ADPLUG_COPLPROPS
    COPLprops opls[2];
    opls[0].opl = opl1;
    opls[0].use16bit = true;
    opls[0].stereo = false;
    opls[1].opl = opl2;
    opls[1].use16bit = true;
    opls[1].stereo = false;
    opl = new CSurroundopl(opls, opls + 1, true);
#else
    opl = new CSurroundopl(opl1, opl2, true);
#endif
    player = CAdPlug::factory(filename, opl);
    ended = (player == NULL);
}

// Destructor.
adplug_player::~adplug_player() {
    delete opl;

}

// This routine is taken from AdPlay's SDL driver:
// https://github.com/adplug/adplay-unix/blob/master/src/sdl.cc
// Copyright (C) 2001 - 2003 Simon Peter <dn.tlp@gmx.net>
// This code was released by the author under GPL v2.
void adplug_player::fill_buffer(void* audiobuf, int len,
        unsigned char sample_size) {
    static long minicnt = 0;
    if (sample_size == 0) sample_size = 1;
    long i, towrite = len / sample_size;
    char* pos = (char*) audiobuf;
    for (int j = 0; j < len; j++) {
        pos[j] = 0;
    }
    if (ended) return;
    // Prepare audiobuf with emulator output
    while (towrite > 0) {
        while (minicnt < 0) {
            minicnt += spectrum_analyzer::SAMPLING_RATE;
            bool end_reached = !player->update();
            if (end_reached && continuous) {
                player->rewind();
            } else if (end_reached) {
                ended = true;
            }
        }
        float refresh = player->getrefresh();
        i = min(towrite,
                (long)(minicnt / ((refresh == 0)? 1 : refresh) + 4) & ~3);
        opl->update((short *)pos, i);
        pos += i * sample_size; towrite -= i;
        minicnt -= (long)(player->getrefresh() * i);
    }
}