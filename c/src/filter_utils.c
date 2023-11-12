#include "filter_utils.h"


// Circular wrap of pointer p, relative to array w
void wrap(int M, double *w, double **p) {
    if (*p > w + M)
        *p -= M + 1;  // when *p = w + M + 1, it wraps around to *p = w

    if (*p < w)
        *p += M + 1;  // when *p = w - 1, it wraps around to *p = w + M
}

// Circular wrap of pointer offset q, relative to array w
void wrap2(int M, int *q) {
    if (*q > M)
        *q -= M + 1;  // when *q = M + 1, it wraps around to *q = 0

    if (*q < 0)
        *q += M + 1;  // when *q = -1, it wraps around to *q = M
}

// Delay by D time samples
void delay(int D, double *w) {
    int i;

    for (i = D; i >= 1; i--)  // reverse-order updating
        w[i] = w[i - 1];
}

// Dot product of two length-(M+1) vectors
double dot(int M, double *h, double *w) {
    int i;
    double y;

    for (y = 0, i = 0; i <= M; i++)  // compute dot product
        y += h[i] * w[i];      

    return y;
}