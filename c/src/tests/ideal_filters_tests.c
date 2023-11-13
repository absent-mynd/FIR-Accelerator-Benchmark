#include "ideal_filters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define EPSILON 1e-6

// Assertion and utility functions
#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf("Assertion failed: %s\n", message); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

int arrays_almost_equal(double *arr1, double *arr2, int N) {
    for (int i = 0; i < N; ++i) {
        if (fabs(arr1[i] - arr2[i]) > EPSILON) {
            return 0;  // Arrays are not equal
        }
    }
    return 1;  // Arrays are equal
}

// Test functions for ideal filters
void test_ideal_bandpass_filter() {
    double h[5];
    ideal_bandpass_filter(h, 5, 0.2, 0.5);

    // Expected values are generated from ideal_filters_ref_data.py
    double expected[5] = { -0.03198677781065059, 0.18716363098329009, 0.7924562667427429, 0.18716363098329009, -0.03198677781065059 };
    
    ASSERT(arrays_almost_equal(h, expected, 5), "Bandpass filter test failed.");
}


void test_ideal_differentiator() {
    double h[5];
    ideal_differentiator(h, 5);

    // Expected values
    double expected[5] = { 0, -0.34822681585073323, 1.5707963267948966, -0.34822681585073345, 0};
    
    ASSERT(arrays_almost_equal(h, expected, 5), "Differentiator test failed.");
}


void test_ideal_hilbert_transformer() {
    double h[5];
    ideal_hilbert_transformer(h, 5);

    // Expected values
    double expected[5] = {0.0, -0.6366197723675814, 0.0, 0.6366197723675814, 0.0};
    
    ASSERT(arrays_almost_equal(h, expected, 5), "Hilbert transformer test failed.");
}


void test_ideal_low_high_pass_filter() {
    double h_lp[5], h_hp[5];
    ideal_low_high_pass_filter(h_lp, 5, 0.3, 0); // Lowpass
    ideal_low_high_pass_filter(h_hp, 5, 0.3, 1); // Highpass

    // Expected values for lowpass and highpass
    double expected_lp[5] = {0.020103708268285354, 0.23086668180542194, 0.4980592198525855, 0.23086668180542194, 0.020103708268285354};
    double expected_hp[5] = {-0.012694426759411575, -0.14578007919019934, 0.7338286951384244, -0.14578007919019934, -0.012694426759411575};
    
    ASSERT(arrays_almost_equal(h_lp, expected_lp, 5), "Lowpass filter test failed.");
    ASSERT(arrays_almost_equal(h_hp, expected_hp, 5), "Highpass filter test failed.");
}


// Test functions for edge cases
void test_ideal_bandpass_filter_edge_cases() {
    double h[1];

    // Test with N = 0
    ideal_bandpass_filter(h, 0, 0.2, 0.5);

    // Test with negative frequencies
    ideal_bandpass_filter(h, 5, -0.1, -0.2);

    // Test with f1 > f2
    ideal_bandpass_filter(h, 5, 0.5, 0.2);

    // not a big deal, behaviour here is undefined.  just shouldn't crash
}


void test_ideal_differentiator_edge_cases() {
    double h[1];

    // Test with N = 1 (should return 0 as the value)
    ideal_differentiator(h, 1);
    ASSERT(fabs(h[0]) < EPSILON, "Differentiator N=1 test failed.");
}


void test_ideal_hilbert_transformer_edge_cases() {
    double h[1];

    // Test with N = 1 (should return 0 as the value)
    ideal_hilbert_transformer(h, 1);
    ASSERT(fabs(h[0]) < EPSILON, "Hilbert transformer N=1 test failed.");
}


void test_ideal_low_high_pass_filter_edge_cases() {
    double h[1];

    // Test with N = 1
    ideal_low_high_pass_filter(h, 1, 0.3, 0); // Lowpass
    ASSERT(fabs(h[0] - 0.6) < EPSILON, "Lowpass filter N=1 test failed.");

    ideal_low_high_pass_filter(h, 1, 0.3, 1); // Highpass
    ASSERT(fabs(h[0] - 0.4) < EPSILON, "Highpass filter N=1 test failed.");

    // Test with invalid cutoff frequency (outside 0 to 0.5 range)
    ideal_low_high_pass_filter(h, 5, -0.1, 0); // Lowpass

    ideal_low_high_pass_filter(h, 5, 1.1, 1); // Highpass
    
    // not a big deal, behaviour here is undefined.  just shouldn't crash
}


// Main function running all tests
int main() {
    test_ideal_bandpass_filter();
    test_ideal_differentiator();
    test_ideal_hilbert_transformer();
    test_ideal_low_high_pass_filter();

    test_ideal_bandpass_filter_edge_cases();
    test_ideal_differentiator_edge_cases();
    test_ideal_hilbert_transformer_edge_cases();
    test_ideal_low_high_pass_filter_edge_cases();

    printf("All tests passed successfully.\n");
    return EXIT_SUCCESS;
}
