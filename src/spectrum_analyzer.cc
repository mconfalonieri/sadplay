/*
 * sadplay - AdLib music player with graphics.
 * 
 * spectrum_analyzer.cc - frequency analyzer implementation
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

#include "spectrum_analyzer.h"

#include <cmath>

// Constructor. It allocates the FFT plan.
spectrum_analyzer::spectrum_analyzer(frequency_bar* fbar) :
        plan(NULL), fbar(fbar) {

    // Allocate the in and out buffers.
    in_buffer = fftw_alloc_real(IN_BUFFER_SIZE);
    out_buffer = fftw_alloc_complex(OUT_BUFFER_SIZE);

    // Prepares the plan and the pre-calculated hann values
    plan = fftw_plan_dft_r2c_1d(IN_BUFFER_SIZE, in_buffer, out_buffer,
            FFTW_ESTIMATE);

    hann_multipliers = new double[IN_BUFFER_SIZE];
    prepare_hann_multipliers();
}

// Destructor.
spectrum_analyzer::~spectrum_analyzer() {
    delete[] hann_multipliers;
    fftw_destroy_plan(plan);
    fftw_free(out_buffer);
    fftw_free(in_buffer);
}

// Acquires a sample and performs the FFT.
void spectrum_analyzer::perform(int n, const short* raw_buffer) {
    acquire(n, raw_buffer);
    fftw_execute(plan);
    fbar->acquire_fft(SAMPLING_RATE, OUT_BUFFER_SIZE, out_buffer);
}

// Acquires the raw buffer.
void spectrum_analyzer::acquire(int n, const short* raw_buffer) {
   int bytes = n * 2;
    for (
            int in_pos = 0, raw_pos = 0;
            raw_pos < bytes;
            in_pos++, raw_pos += 2
    ) {
        double h = hann_multipliers[in_pos];

        // Prepare the sample using the window function.
        in_buffer[in_pos] = h * acquire_sample(bytes, raw_pos, raw_buffer);
    } 
}

// Hann window function.
double spectrum_analyzer::hann(int i, int n) {
    double sqrt_hann = sin(M_PI * (double) i / (double) n);
    return sqrt_hann * sqrt_hann;
}

// Prepares the array with the Hann multipliers.
void spectrum_analyzer::prepare_hann_multipliers() {
    for (int i = 0; i < IN_BUFFER_SIZE; i++) {
        hann_multipliers[i] = hann(i, IN_BUFFER_SIZE);
    }
}