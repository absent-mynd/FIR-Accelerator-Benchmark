#include "filter_utils.h"
#include <math.h>
#include <stdio.h>

#ifndef IDEAL_FILTERS_H
#define IDEAL_FILTERS_H

void ideal_bandpass_filter(double* h, int N, double f1, double f2);
void ideal_differentiator(double* h, int N);
void ideal_hilbert_transformer(double* h, int N);
void ideal_low_high_pass_filter(double* h, int N, double fc, int isHighpass);

#endif // IDEAL_FILTERS_H
