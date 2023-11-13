#ifndef FILTER_WINDOWS_H
#define FILTER_WINDOWS_H

void apply_hamming_window(double* h, int N);
void apply_hanning_window(double* h, int N);
void apply_blackman_window(double* h, int N);
void apply_kaiser_window(double* h, int N, double beta);

#endif // FILTER_WINDOWS_H
