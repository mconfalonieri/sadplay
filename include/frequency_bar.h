/*
 * sadplay - AdLib music player with graphics.
 * 
 * frequency_bar.h - header of the frequency bar.
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

#ifndef _SADPLAY_FREQUENCY_BAR_
#define _SADPLAY_FREQUENCY_BAR_

#include <fftw3.h>

#include "channel_bar.h"

/**
 * Frequency bar implemented on a channel bar.
 */
class frequency_bar {
    public:
        /**
         * Spectrometer bars.
         */
        const static int CHANNEL_BARS = 12;

        /**
         * Spectrometer limits.
         */
        const static double CHANNEL_LIMITS[];

        /**
         * Constructor. It accepts a channel bar that must have 12 channels.
         * 
         * @param   cbar                the channel bar
         */
        frequency_bar(channel_bar* cbar);

        /**
         * Destructor.
         */
        ~frequency_bar();

        /**
         * Acquires the results of the FFT. It loads the results in the
         * channel bar.
         * 
         * @param   sample_rate         the sample rate, expressed in samples
         *                              per second
         * @param   num_entries         number of entries. For a R2C FFT, it
         *                              should be N/2 + 1
         * @param   result              the result, expressed as an array of
         *                              complex numbers.
         */
        void acquire_fft(int sample_rate, int num_samples,
                const fftw_complex* result);

    protected:
        /**
         * Calculates the amplitude in decibels and sets the values in an
         * integer array.
         * 
         * @param   in_buffer           the buffer containing the squared
         *                              magnitudes on which the calculation
         *                              applies.
         * @param   out_buffer          the output buffer.
         */
        void prepare_channels(const double* in_buffer, int* out_buffer);

    private:
        /**
         * Index of the real part of a complex number.
         */
        const static int FFTW_REAL = 0;

        /**
         * Index of the imaginary part of a complex number.
         */
        const static int FFTW_IMAG = 1;

        /**
         * Calculates the frequency of an entry.
         * 
         * @param   i                   i-th entry of the FFT result array
         * @param   n                   number of entries in the FFT result
         *                              array
         * @param   sample_rate         the sample rate, expressed in samples
         *                              per second
         * 
         * @return  the frequency of the i-th entry, expressed in cycles per
         *          second
         */
        inline double get_frequency(int i, int n, int sample_rate) {
            return (double) sample_rate * (double) i / (double) n / 2;
        }

        /**
         * Returns the squared magnitude (energy) of a complex number.
         * 
         * @param   c                   complex number
         * 
         * @return  the squared magnitude of the parameter
         */
        inline double squared_magnitude(const fftw_complex c) {
            return c[FFTW_REAL] * c[FFTW_REAL] + c[FFTW_IMAG] * c[FFTW_IMAG];
        }

        /**
         * Pointer to the channel bar.
         */
        channel_bar* cbar;
};

#endif // _SADPLAY_FREQUENCY_BAR_
