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

// Constructor. It does all the calculations required to size the buffers and
// allocate the FFT plan.
spectrum_analyzer::spectrum_analyzer(int duration): plan(NULL) {
    in_raw_buffer_size = get_in_raw_buffer_size(duration);
    in_buffer_size = get_in_buffer_size();
    out_buffer_size = get_out_buffer_size();

    // Allocate the in and out buffers.
    in_buffer = fftw_alloc_real(in_buffer_size);
    out_buffer = fftw_alloc_complex(out_buffer_size);

    plan = fftw_plan_dft_r2c_1d(in_buffer_size, in_buffer, out_buffer, )
}

        /**
         * Destructor.
         */
        spectrum_analyzer::~spectrum_analyzer();

        /**
         * Acquires a new sample.
         * 
         * @param   raw_buffer      the raw sample buffer
         */
        void spectrum_analyzer::acquire(short* raw_buffer);

    protected:
        /**
         * Buffer size for one second.
         */
        const static int RAW_BUFFER_SIZE_1S = SAMPLING_RATE * CHANNELS * BYTES_PER_SAMPLE;

    private:
        /**
         * Calculates the raw buffer size based on duration.
         * 
         * @param   duration        duration in milliseconds
         * 
         * @return  the raw buffer size (before interpolation)
         */
        inline int get_in_raw_buffer_size(int duration) {
            return RAW_BUFFER_SIZE_1S * duration / 1000;
        }

        /**
         * Calculates the input mono buffer size.
         */
        inline int get_in_buffer_size() { return in_raw_buffer_size / 2; }

        /**
         * Calculates the output buffer size.
         * 
         * @return the output buffer size
         */
        inline int get_out_buffer_size() { return in_buffer_size / 2 + 1; }

        /**
         * Interpolates two channels into one.
         * 
         * @param   in              the input array
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