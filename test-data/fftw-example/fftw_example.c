/* Start reading here */

#include <fftw3.h>

/*
N = 8192;
Sample_Rate = 44100;
float[] myAudio = new Float[N];
myAudio = getAudio();
Complex[] myFFT_Audio = FFT(myAudio);  //Returns N complex values

//Get Array of frequency Values
float[] frequencies = new float[N]
for( i = 0 ; i < N; i++)
   { frequencies[i] = i * (Sample_Rate / N) - (Sample_Rate / 2); }

//Get Amplitudes
float[] Amplitudes = new float[N]
for( i = 0; i < N; i++)
  { Amplitudes[i] = myFFT_Audio[i].Magnitude(); }

//Plot Frequencies vs Amplitudes - will plot for frequencies -fs/2 to fs/2
PLOT(frequencies , Amplitudes);
*/
/* Never mind this bit */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>

#define REAL 0
#define IMAG 1

#define SAMPLE_RATE 132000
#define FILENAME "wave.s16"

off_t fsize(const char *filename) {
    struct stat st; 

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1; 
}


double hann(int i, int nn) {
    double sqrt_hann = sin(M_PI * (double) i / (double) nn);
    return sqrt_hann * sqrt_hann;
}

void copy_to_signal(int offset, double* signal, short* buffer, int n, int points) {
    for (int idx = 0; idx < n; idx++) {
        double m = (double) buffer[idx];
        signal[offset] = hann(offset, points) * (m / (double) INT16_MAX);
        offset++;
    }
}
void acquire_from_somewhere(int points, double* signal) {
    // Open PCM file and transform to mono
    FILE* fp = fopen(FILENAME, "r");
    short buffer[100];
    int n;
    int ptr = 0;
    while(!feof(fp)) {
        n = fread(buffer, sizeof(short), 100, fp);
        copy_to_signal(ptr, signal, buffer, n, points);
        ptr += n;
    }
    fclose(fp);
}

double calc_mag(int num, int start, double* array) {
    double sum = 0;
    for (int i = 0; i < num; i++) {
        double val = array[start + i];
        sum += val;
    }
    return sum;
}

void do_something_with(int points, fftw_complex* result) {
    int i;
    double max = 0;
    double* mag_array = malloc(sizeof(double) * points);
     for (i = 0; i < points; ++i) {
        double mag = result[i][REAL] * result[i][REAL] +
                          result[i][IMAG] * result[i][IMAG];
        mag_array[i] = (mag > 0)? mag : 0;
        if (mag > max) max = mag;
    }
    
    int cpoints = 1000;
    int many_to_one = (points / 2) / cpoints;
    double freq_step = (double) SAMPLE_RATE / points;
    for (int j = 0; j < (points / 2); j+= many_to_one) {
        double freq = (freq_step * j) / 1000;
        double mag = 10*log10(calc_mag(many_to_one, j, mag_array));
        int magint = (int) (mag * 50.0 / 120.0);
        printf("[%4.1f kHz %6.1f] ", freq, mag);
        for (int i = 0; i < magint; i++) {
            printf("|");
        }
        printf("\n");
    }

    free(mag_array);
}


/* Resume reading here */

int main() {
    int points = fsize(FILENAME);
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
