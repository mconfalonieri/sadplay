/* Start reading here */

#include <fftw3.h>


/* Never mind this bit */

#include <malloc.h>
#include <stdio.h>
#include <math.h>

#define REAL 0
#define IMAG 1

double hamming (int i, int nn) {
  return ( 0.54 - 0.46 * cos (2.0*M_PI*(double)i/(double)(nn-1)) );
}

void acquire_from_somewhere(int points, double* signal) {
    // Open PCM file and transform to mono
    FILE* fp = fopen("sample.s16", "r");
    short buffer[100];
    int n;
    int ptr = 0;
    while(!feof(fp)) {
        n = fread(buffer, sizeof(short), 100, fp);
        for (int idx = 0; idx < 2; idx += 2) {
            int j = idx / 2;
            double l = (double) buffer[idx];
            double r = (double) buffer[idx + 1];
            double m = (l + r) / 2;
            signal[ptr + j] = hamming(j, points) * m;
            if ((idx % 60000) == 0) {
                printf("%g => %g\n", m, signal[ptr + j]);
            }
        }
        ptr += n / 2;
    }
    
}

double interpolate(int num, int start, double* array) {
    double sum = 0;
    for (int i = 0; i < num; i++) {
        sum += array[start + i];
    }
    return sum / num;
}

void do_something_with(int points, fftw_complex* result) {
    int i;
    double* mag_array = malloc(sizeof(double) * points);
    double max = 1;
    for (i = 0; i < points; ++i) {
        double mag = 10 * log10(result[i][REAL] * result[i][REAL] +
                          result[i][IMAG] * result[i][IMAG]);
        mag_array[i] = (mag > 0)? mag : 0;
        if (mag > max) max = mag;
    }
    int cpoints = 20;
    int many_to_one = (points / 2) / cpoints;
    double freq_step = 44100.0 / points;
    printf("%g / %d = %g (%g)\n", 44100.0, points, freq_step, freq_step * many_to_one);
    for (int j = 0; j < (points / 2); j+= many_to_one) {
        double freq = (freq_step * j) / 1000;
        double mag = interpolate(many_to_one, j, mag_array);
        int magint = (int) ((mag / max) * 70);
        printf("[%4.1f kHz %6.1f] ", freq, mag);
        for (int i = 0; i < magint; i++) {
            printf("¦");
        }
        printf("\n");
    }
    free(mag_array);
}


/* Resume reading here */

int main() {
    int points = 661500;
    int out_points = points / 2 + 1;
    double* data = fftw_alloc_real(points);
    fftw_complex* result = fftw_alloc_complex(out_points);

    fftw_plan plan = fftw_plan_dft_r2c_1d(points, data, result, FFTW_ESTIMATE);

    acquire_from_somewhere(points, data);
    fftw_execute(plan);
    do_something_with(points, result);

    fftw_destroy_plan(plan);
    fftw_free(data);
    return 0;
}
