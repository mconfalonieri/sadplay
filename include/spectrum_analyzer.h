/*
 * sadplay - AdLib music player with graphics.
 * 
 * spectrum_analyzer.h - frequency analyzer header
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

#ifndef _SADPLAY_SPECTRUM_ANALYZER_H_
#define _SADPLAY_SPECTRUM_ANALYZER_H_

#include <vector>

#include <fftw3.h>

#include "frequency_bar.h"

/**
 * Spectrum analyzer class. This class analyzes the spectrum of the data
 * provided. The samples are always assumed to be PCM-encoded, signed, 16-bit
 * with a sampling rate of 44.1kHz.
 */
class spectrum_analyzer {
    public:
        /**
         * Sampling rate.
         */
        const static int SAMPLING_RATE = 44100;

        /**
         * Input buffer size.
         */
        const static int IN_BUFFER_SIZE = 4096;

        /**
         * Raw input buffer size (stereo).
         */
        const static int IN_RAW_BUFFER_SIZE = IN_BUFFER_SIZE * 2;

        /**
         * Output buffer size.
         */
        const static int OUT_BUFFER_SIZE = IN_BUFFER_SIZE / 2 + 1;

        /**
         * Constructor.
         * 
         * @param   bar             frequency bar
         */
        spectrum_analyzer(frequency_bar* bar);

        /**
         * Destructor.
         */
        ~spectrum_analyzer();

        /**
         * Acquires a new sample buffer and performs the FFT. If the
         * available data is less than the full buffer, it will be
         * zero-padded.
         * 
         * @param   n               number of samples
         * @param   raw_buffer      the raw sample buffer
         */
        void perform(int n, const short* raw_buffer);

    protected:
        /**
         * Acquires the input array.
         * 
         * @param   n               number of samples
         * @param   raw_buffer      the raw sample buffer
         */
        void acquire(int n, const short* raw_buffer);

        /**
         * Acquires data from the buffer if present, or pad with zero.
         */
        inline short acquire_sample(int bytes, int pos, const short* buffer) {
            return (pos < bytes)? interpolate_stereo(buffer + pos) : 0;
        }

        /**
         * Interpolates two channels into one.
         * 
         * @param   in              the input array
         * 
         * @return  the interpolated value
         */
        inline short interpolate_stereo(const short in[2]) {
            return (in[0] + in[1]) / 2;
        }

        /**
         * Hann window function.
         * 
         * @param   i               the position in the input buffer
         * @param   n               the number of samples
         * 
         * @return  the multiplier for the i-th position
         */
        double hann(int i, int n);

        /**
         * Prepares the Hann multipliers.
         */
        void prepare_hann_multipliers();
        
    private:
       /**
         * The input buffer.
         */
        double* in_buffer;

        /**
         * The output buffer.
         */
        fftw_complex* out_buffer;

        /**
         * The transformation plan.
         */
        fftw_plan plan;

        /**
         * Frequency bar.
         */
        frequency_bar* fbar;

        /**
         * Hann coefficients.
         */
        double* hann_multipliers;
};

#endif // _SADPLAY_SPECTRUM_ANALYZER_H_