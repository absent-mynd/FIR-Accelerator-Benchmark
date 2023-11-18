#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846
#include <math.h>

double bessel_i0(double x) {
    double eps = 1e-9;
    int n = 1;
    double S = 1, D = 1, T;

    while (D > eps * S) {
        T = x / (2 * n++);
        D *= T * T;
        S += D;
    }

    return S;
}

// Window Functions
double hamming_window(int n, int N) {
    return 0.54 - 0.46 * cos(2 * PI * n / (N - 1));
}

double hanning_window(int n, int N) {
    return 0.5 * (1 - cos(2 * PI * n / (N - 1)));
}

double blackman_window(int n, int N) {
    const double a0 = (1 - 0.16) / 2, a1 = 0.5, a2 = 0.16 / 2;
    return a0 - a1 * cos(2 * PI * n / (N - 1)) + a2 * cos(4 * PI * n / (N - 1));
}

double kaiser_window(int n, int N, double beta) {
    double t = (2.0 * n) / (N - 1) - 1.0;
    return bessel_i0(beta * sqrt(1 - t * t)) / bessel_i0(beta);
}

// Apply specific window types
void apply_hamming_window(double* h, int N) {
    for (int n = 0; n < N; n++) {
        h[n] *= hamming_window(n, N);
    }
}

void apply_hanning_window(double* h, int N) {
    for (int n = 0; n < N; n++) {
        h[n] *= hanning_window(n, N);
    }
}

void apply_blackman_window(double* h, int N) {
    for (int n = 0; n < N; n++) {
        h[n] *= blackman_window(n, N);
    }
}

void apply_kaiser_window(double* h, int N, double beta) {
    for (int n = 0; n < N; n++) {
        h[n] *= kaiser_window(n, N, beta);
    }
}
