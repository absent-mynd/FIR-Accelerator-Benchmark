#include "ideal_filters.h"
#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846

// Sinc function
double sinc(double x) {
    if (x == 0.0) {
        return 1.0;
    } else {
        return sin(PI * x) / (PI * x);
    }
}


// Ideal Bandpass Filter Impulse Response
// h is the array of length N to store the impulse response
// N is the number of points in the impulse response
// f1 is the lower cutoff frequency
// f2 is the upper cutoff frequency
void ideal_bandpass_filter(double* h, int N, double f1, double f2) {
    int M = (N - 1) / 2;
    for (int n = 0; n < N; n++) {
        double x = n - M;
        h[n] = 2 * f2 * sinc(2 * f2 * x) - 2 * f1 * sinc(2 * f1 * x);
    }
}

// Ideal Differentiator Impulse Response
// h is the array of length N to store the impulse response
// N is the number of points in the impulse response
void ideal_differentiator(double* h, int N) {
    int M = (N - 1) / 2;
    for (int n = 0; n < N; n++) {
        if (n == M) {
            h[n] = 0;
        } else {
            double x = n - M;
            h[n] = cos(PI * x) / x;
        }
    }
}

// Ideal Hilbert Transformer Impulse Response
// h is the array of length N to store the impulse response
// N is the number of points in the impulse response
void ideal_hilbert_transformer(double* h, int N) {
    int M = (N - 1) / 2;
    for (int n = 0; n < N; n++) {
        if (n == M) {
            h[n] = 0;
        } else {
            double x = n - M;
            h[n] = 2 / (PI * x) * (1 - cos(PI * x));
        }
    }
}

// Ideal Lowpass/Highpass Filter Impulse Response
// h is the array of length N to store the impulse response
// N is the number of points in the impulse response
// fc is the cutoff frequency
// isHighpass is a boolean flag indicating whether to compute a highpass filter or a lowpass filter
void ideal_low_high_pass_filter(double* h, int N, double fc, int isHighpass) {
    int M = (N - 1) / 2;
    for (int n = 0; n < N; n++) {
        double x = n - M;
        if (n == M) {
            h[n] = isHighpass ? (1 - 2 * fc) : (2 * fc);
        } else {
            h[n] = isHighpass ? (-2 * fc * sinc(2 * fc * x)) : (2 * fc * sinc(2 * fc * x));
        }
    }
}
