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

int arrays_almost_equal(double *arr1, double *arr2, int N) {
    for (int i = 0; i < N; ++i) {
        if (fabs(arr1[i] - arr2[i]) > EPSILON) {
            return 0;  // Arrays are not equal
        }
    }
    return 1;  // Arrays are equal
}

// Test functions for window functions
void test_hamming_window() {
    const int N = 5;
    double h[N] = {1, 1, 1, 1, 1};
    apply_hamming_window(h, N);

    double expected[N] = {/* expected values here */};
    
    ASSERT(arrays_almost_equal(h, expected, N), "Hamming window test failed.");
}

void test_hanning_window() {
    const int N = 5;
    double h[N] = {1, 1, 1, 1, 1};
    apply_hanning_window(h, N);

    double expected[N] = {/* expected values here */};
    
    ASSERT(arrays_almost_equal(h, expected, N), "Hanning window test failed.");
}

void test_blackman_window() {
    const int N = 5;
    double h[N] = {1, 1, 1, 1, 1};
    apply_blackman_window(h, N);

    double expected[N] = {/* expected values here */};
    
    ASSERT(arrays_almost_equal(h, expected, N), "Blackman window test failed.");
}

void test_kaiser_window() {
    const int N = 5;
    double beta = 5.0;
    double h[N] = {1, 1, 1, 1, 1};
    apply_kaiser_window(h, N, beta);

    double expected[N] = {/* expected values here */};
    
    ASSERT(arrays_almost_equal(h, expected, N), "Kaiser window test failed.");
}

// Edge case tests for window functions
void test_window_functions_edge_cases() {
    const int N = 1;  // Testing with N = 1
    double h[N] = {1};

    apply_hamming_window(h, N);
    ASSERT(fabs(h[0] - 1.0) < EPSILON, "Hamming window edge case test failed.");

    apply_hanning_window(h, N);
    ASSERT(fabs(h[0] - 1.0) < EPSILON, "Hanning window edge case test failed.");

    apply_blackman_window(h, N);
    ASSERT(fabs(h[0] - 1.0) < EPSILON, "Blackman window edge case test failed.");

    apply_kaiser_window(h, N, 5.0);
    ASSERT(fabs(h[0] - 1.0) < EPSILON, "Kaiser window edge case test failed.");
}

// Main function running all tests
int main() {
    test_hamming_window();
    test_hanning_window();
    test_blackman_window();
    test_kaiser_window();

    test_window_functions_edge_cases();

    printf("All window function tests passed successfully.\n");
    return EXIT_SUCCESS;
}
