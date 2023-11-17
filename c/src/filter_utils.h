#include "fixedptc.h"
#ifndef FILTER_UTILS_H
#define FILTER_UTILS_H

// Function declarations for utility functions
void wrap(int M, double *w, double **p);
void wrap_fixed(int M, fixedpt *w, fixedpt **p);
void wrap2(int M, int *q);
void delay(int D, double *w);
void delay_fixed(int D, fixedpt *w);
double dot(int M, double *h, double *w);
fixedpt dot_fixed(int M, fixedpt *h, fixedpt *w);

#endif // FILTER_UTILS_H
