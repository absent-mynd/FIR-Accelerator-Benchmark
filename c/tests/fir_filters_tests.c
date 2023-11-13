#include "fir_filters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define EPSILON 1e-6
#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf("Assertion failed: %s\n", message); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)


// Helper function to test FIR filter
void test_fir_filter(double (*fir_func)(int, double *, double *, double), 
                     int M, double *h, double *w, double *x, int x_len, 
                     double *expected_output) {
    double y;

    reset_filter_state(M, w);

    // Process each input sample and compare output
    for (int i = 0; i < x_len; ++i) {
        y = fir_func(M, h, w, x[i]);

        // Check if the output matches the expected value
        ASSERT(fabs(y - expected_output[i]) < EPSILON, "Output does not match expected.");
    }
}

void test_cfir_filter(double (*cfir_func)(int, double *, double *, double **, double), 
                     int M, double *h, double *w, double **p, double *x, int x_len, 
                     double *expected_output) {
    double y;

    reset_filter_state(M, w);

    // Process each input sample and compare output
    for (int i = 0; i < x_len; ++i) {
        y = cfir_func(M, h, w, p, x[i]);

        // Check if the output matches the expected value
        ASSERT(fabs(y - expected_output[i]) < EPSILON, "Output does not match expected.");
    }
}

void test_cfir2_filter(double (*cfir2_func)(int, double *, double *, int *, double), 
                     int M, double *h, double *w, double *q, double *x, int x_len, 
                     double *expected_output) {
    double y;

    reset_filter_state(M, w);

    // Process each input sample and compare output
    for (int i = 0; i < x_len; ++i) {
        y = cfir2_func(M, h, w, q, x[i]);

        // Check if the output matches the expected value
        ASSERT(fabs(y - expected_output[i]) < EPSILON, "Output does not match expected.");
    }
}


void reset_filter_state(int M, double *w) {
    for (int i = 0; i <= M; i++) w[i] = 0;
}


int main() {
    // Test parameters
    int M = 3;  // Filter order
    double h[] = {0.1, 0.2, 0.3, 0.4};  // Filter coefficients
    double w[] = {0, 0, 0, 0};  // Filter state

    
    int x_len = 10; // Length of input signal
    double x[] = {
        0.0, 
        0.9510565162951535, 
        0.5877852522924732, 
        -0.5877852522924734, 
        -0.9510565162951536, 
        0, 0.9510565162951538, 
        0.5877852522924734, 
        -0.5877852522924728, 
        -0.9510565162951538
    } ;  // Input signal, obtained from Python script (see fir_filters_tests.py)
    double expected_output[] = {
        0.0, 
        0.09510565162951536, 
        0.24898982848827805, 
        0.34409548011779334, 
        0.34409548011779334, 
        -0.13143277802978345, 
        -0.42532540417602, 
        -0.13143277802978343, 
        0.34409548011779345, 
        0.34409548011779356, 
        -0.13143277802978323, 
        -0.5204310558055353, 
        -0.38042260651806153
    };  // Expected output, obtained from Python script (see fir_filters_tests.py)
    // Note: expected_output is longer than x because of the filter delay

    // Testing fir
    test_fir_filter(fir, M, h, w, x, x_len, expected_output);


    // Testing fir2 (assuming dot and delay functions are defined)
    test_fir_filter(fir2, M, h, w, x, x_len, expected_output);

    // Testing fir3
    test_fir_filter(fir3, M, h, w, x, x_len, expected_output);

    // Testing cfir
    double *p = w;  // Setup for cfir circular buffer
    test_cfir_filter(cfir, M, h, w, &p, x, x_len, expected_output);

    // Testing cfir1
    p = w;  // Reset pointer for cfir1
    test_cfir_filter(cfir1, M, h, w, &p, x, x_len, expected_output);

    // Testing cfir2
    int q = 0;  // Setup for cfir2 circular buffer
    test_cfir2_filter(cfir2, M, h, w, &q, x, x_len, expected_output);

    printf("All tests passed successfully.\n");
    return EXIT_SUCCESS;
}