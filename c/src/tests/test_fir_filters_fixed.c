#include "fir_filters_fixed.h"
#include "fixedptc.h"
#include <stdio.h>
#include <stdlib.h>


#define EPSILON 1e-6

#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf("Assertion failed: %s\n", message); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

void reset_filter_state(int M, fixedpt *w) {
    for (int i = 0; i <= M; i++) w[i] = 0;
}

// Update test functions to use fixedpt-point arithmetic
void test_fir_filter(fixedpt (*fir_func)(int, fixedpt *, fixedpt *, fixedpt),
                     int M, fixedpt *h, fixedpt *w, fixedpt *x, int x_len,
                     fixedpt *expected_output) {
    fixedpt y;

    reset_filter_state(M, w);

    for (int i = 0; i < x_len; ++i) {
        y = fir_func(M, h, w, x[i]);
        printf("y = %f = %lld\n", fixedpt_todouble(y), y);
        printf("expected_output = %f = %lld\n", fixedpt_todouble(expected_output[i]), expected_output[i]);
        ASSERT(fixedpt_todouble(fixedpt_abs(y - expected_output[i])) <= EPSILON, "Output does not match expected for fir.");
    }
}

void test_cfir_filter(fixedpt (*cfir_func)(int, fixedpt *, fixedpt *, fixedpt **, fixedpt),
                      int M, fixedpt *h, fixedpt *w, fixedpt **p, fixedpt *x, int x_len,
                      fixedpt *expected_output) {
    fixedpt y;

    reset_filter_state(M, w);

    for (int i = 0; i < x_len; ++i) {
        y = cfir_func(M, h, w, p, x[i]);

        ASSERT(fixedpt_todouble(fixedpt_abs(y - expected_output[i])) <= EPSILON, "Output does not match expected for cfir.");
    }
}

void test_cfir2_filter(fixedpt (*cfir2_func)(int, fixedpt *, fixedpt *, int *, fixedpt),
                      int M, fixedpt *h, fixedpt *w, int *q, fixedpt *x, int x_len,
                      fixedpt *expected_output) {
    fixedpt y;

    reset_filter_state(M, w);

    for (int i = 0; i < x_len; ++i) {
        y = cfir2_func(M, h, w, q, x[i]);
        ASSERT(fixedpt_todouble(fixedpt_abs(y - expected_output[i])) <= EPSILON, "Output does not match expected for cfir2.");
    }
}

int main() {
    // Test parameters
    int M = 3;  // Filter order
    fixedpt h[] = {fixedpt_fromdouble(0.1), fixedpt_fromdouble(0.2), fixedpt_fromdouble(0.3), fixedpt_fromdouble(0.4)};
    fixedpt w[4] = {0};  // Filter state

    int x_len = 10;  // Length of input signal
    fixedpt x[] = {
        fixedpt_fromdouble(0.0), 
        fixedpt_fromdouble(0.95105651), 
        fixedpt_fromdouble(0.58778525), 
        fixedpt_fromdouble(-0.5877852), 
        fixedpt_fromdouble(-0.9510565), 
        fixedpt_fromdouble(0),
        fixedpt_fromdouble(0.95105651), 
        fixedpt_fromdouble(0.58778525), 
        fixedpt_fromdouble(-0.5877852), 
        fixedpt_fromdouble(-0.9510565)
    } ;  // Input signal, obtained from Python script (see fir_filters_tests.py)
    fixedpt expected_output[] = {
        fixedpt_fromdouble(0.0), 
        fixedpt_fromdouble(0.09510565), 
        fixedpt_fromdouble(0.24898982), 
        fixedpt_fromdouble(0.34409548), 
        fixedpt_fromdouble(0.34409548), 
        fixedpt_fromdouble(-0.1314327), 
        fixedpt_fromdouble(-0.4253254), 
        fixedpt_fromdouble(-0.1314327), 
        fixedpt_fromdouble(0.34409548), 
        fixedpt_fromdouble(0.34409548), 
        fixedpt_fromdouble(-0.1314327), 
        fixedpt_fromdouble(-0.5204310), 
        fixedpt_fromdouble(-0.3804226)
    };

    // Testing fir
    printf("Testing fir_fixed\n");
    test_fir_filter(fir_fixed, M, h, w, x, x_len, expected_output);

    printf("Testing fir2_fixed\n");
    test_fir_filter(fir2_fixed, M, h, w, x, x_len, expected_output);

    printf("Testing fir3_fixed\n");
    test_fir_filter(fir3_fixed, M, h, w, x, x_len, expected_output);

    // Testing cfir
    fixedpt *p = w;  // Setup for cfir circular buffer
    printf("Testing cfir_fixed\n");
    test_cfir_filter(cfir_fixed, M, h, w, &p, x, x_len, expected_output);

    // Testing cfir1
    printf("Testing cfir1_fixed\n");
    test_cfir_filter(cfir1_fixed, M, h, w, &p, x, x_len, expected_output);

    // Testing cfir2
    int q = 0;  // Setup for cfir2 circular buffer
    printf("Testing cfir2_fixed\n");
    test_cfir2_filter(cfir2_fixed, M, h, w, &q, x, x_len, expected_output);



    printf("All tests passed successfully.\n");
    return EXIT_SUCCESS;
}
