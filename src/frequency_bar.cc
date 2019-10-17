/*
 * sadplay - AdLib music player with graphics.
 * 
 * frequency_bar.cc - implementation of the frequency bar.
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

#include <cassert>
#include <cmath>
#include "frequency_bar.h"

// Frequency limits on each channel.
const double frequency_bar::CHANNEL_LIMITS[] = {
        60.0,       170.0,      310.0,      600.0,
        1000.0,     3000.0,     6000.0,     14000.0,
        16000.0,    18000.0,    20000.0,    100000.0
};

// Constructor. The channel bar MUST have the right number of bars. This is
// enforced with an assert.
frequency_bar::frequency_bar(channel_bar* cbar) {
    int num_channels = cbar->get_numchannels();
    assert(num_channels == CHANNEL_BARS);
    this->cbar = cbar;
}

// Destructor.
frequency_bar::~frequency_bar() {

}

// Acquires the results.
void frequency_bar::acquire_fft(int sample_rate, int num_samples, const fftw_complex* result) {
    double energies[CHANNEL_BARS] = { 0 };
    int channels[CHANNEL_BARS] = { 0 };
    const int LAST_CHANNEL = CHANNEL_BARS - 1;

    int channel = 0;
    for (int i = 0; i < num_samples; i++) {
        double freq = get_frequency(i, num_samples, sample_rate);
        if (freq > CHANNEL_LIMITS[channel] && channel < LAST_CHANNEL) {
            channel++;
        }
        energies[channel] += squared_magnitude(result[i]);
    }

    prepare_channels(energies, channels);
    cbar->update_all(channels);
}

// Prepares the channels to be loaded in the channel bar.
void frequency_bar::prepare_channels(const double* in_buffer, int* out_buffer) {
    for (int i = 0; i < CHANNEL_BARS; i++) {
        double db_value = 10.0 * log10(in_buffer[i]) / 1.4;
        out_buffer[i] = (db_value > 100)? 100 :
                ((db_value < 0)? 0 : (int) db_value);
    }
}