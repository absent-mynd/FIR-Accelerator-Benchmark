#include "fir_filters.h"
#include "fixed.h"
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf("Assertion failed: %s\n", message); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

void reset_filter_state(int M, fixed *w) {
    for (int i = 0; i <= M; i++) w[i] = 0;
}

// Update test functions to use fixed-point arithmetic
void test_fir_filter(fixed (*fir_func)(int, fixed *, fixed *, fixed),
                     int M, fixed *h, fixed *w, fixed *x, int x_len,
                     fixed *expected_output) {
    fixed y;

    reset_filter_state(M, w);

    for (int i = 0; i < x_len; ++i) {
        y = fir_func(M, h, w, x[i]);
        ASSERT(abs(y - expected_output[i]) <= FIXED_POINT_EPSILON, "Output does not match expected.");
    }
}

// Similar updates for test_cfir_filter and test_cfir2_filter...

int main() {
    // Test parameters
    int M = 3;  // Filter order
    fixed h[] = {float_to_fixed(0.1), float_to_fixed(0.2), float_to_fixed(0.3), float_to_fixed(0.4)};
    fixed w[4] = {0};  // Filter state

    int x_len = 10;  // Length of input signal
    fixed x[] = { /* Fixed-point representations of input values */ };
    fixed expected_output[] = { /* Fixed-point representations of expected output values */ };

    // Testing fir
    test_fir_filter(fir, M, h, w, x, x_len, expected_output);

    // ... TODO Testing other filters

    printf("All tests passed successfully.\n");
    return EXIT_SUCCESS;
}
