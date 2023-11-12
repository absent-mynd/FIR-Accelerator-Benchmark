#ifndef FILTER_UTILS_H
#define FILTER_UTILS_H

// Function declarations for utility functions
void wrap(int M, double *w, double **p);
void wrap2(int M, int *q);
void delay(int D, double *w);
double dot(int M, double *h, double *w);

#endif // FILTER_UTILS_H
