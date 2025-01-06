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
#include "frequency_bar.h"

#include <cassert>
#include <cmath>

// Constructor.
frequency_bar::frequency_bar(channel_bar* cbar) {
    num_channels = cbar->get_numchannels();
    freq_limits = cbar->get_channel_limits();
    chan_bar = cbar;
}

// Destructor.
frequency_bar::~frequency_bar() {

}

// Acquires the results.
void frequency_bar::acquire_fft(int sample_rate, int num_samples,
        const fftw_complex* result) {
    double energies[num_channels];
    int channels[num_channels];
    const int LAST_CHANNEL = num_channels - 1;

    int channel = 0;
    for (int i = 0; i < num_samples; i++) {
        double freq = get_frequency(i, num_samples, sample_rate);
        if (freq > freq_limits[channel] && channel < LAST_CHANNEL) {
            channel++;
        }
        energies[channel] += squared_magnitude(result[i]);
    }

    prepare_channels(energies, channels);
    chan_bar->update_all(channels);
}

// Prepares the channels to be loaded in the channel bar.
void frequency_bar::prepare_channels(const double* in_buffer,
        int* out_buffer) {
    for (int i = 0; i < num_channels; i++) {
        double db_value = 10.0 * log10(in_buffer[i]) / 1.4;
        out_buffer[i] = (db_value > 100)? 100 :
                ((db_value < 0)? 0 : (int) db_value);
    }
}