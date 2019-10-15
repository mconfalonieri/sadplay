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

#ifndef _SADPLAY_ANALYZER_H_
#define _SADPLAY_ANALYZER_H_

#include <fftw3.h>

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
         * Number of channels.
         */
        const static int CHANNELS = 2;

        /**
         * Bytes per sample.
         */
        const static int BYTES_PER_SAMPLE = 2;

        /**
         * Constructor. It builds a new spectrum analyzer with a sample
         * duration.
         * 
         * @param   duration        the duration in milliseconds
         */
        spectrum_analyzer(int duration);

        /**
         * Acquires a new sample.
         */
        void acquire(short* in_data);

    private:
        /**
         * Calculates the output buffer size.
         */
        inline int get_out_buffer_size() { return in_buffer_size / 2 + 1; }

        /**
         */
        inline int get_in_raw_buffer_size(int duration) {
            return SAMPLING_RATE * CHANNELS * BYTES_PER_SAMPLE * duration / 1000;
        }

        /**
         * Interpolates two channels into one.
         * 
         * @param   in          the input array
         * 
         * @return  the interpolated value
         */
        inline short interpolate_stereo(short in[2]) { return (in[0] + in[1]) / 2; }

        int in_raw_buffer_size;
        /**
         * The input buffer size.
         */ 
        int in_buffer_size;

        /**
         * The output buffer size.
         */
        int out_buffer_size;

        /**
         * The transformation plan.
         */
        fftw_plan plan;
};

#endif // _SADPLAY_ANALYZER_H_