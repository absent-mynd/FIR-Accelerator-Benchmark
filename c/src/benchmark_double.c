#include "benchmark_double.h"

#define FILTER_LENGTH 1000
#define ITERATIONS 100 // Runtime scales linearly with this value
#define TEST_SIGNAL_LENGTH 10000 // Runtime scales linearly with this value

// Function prototypes for generating test signals
void generateSinusoidal(double *signal, int length, double frequency, double samplingRate);
void generateStepFunction(double *signal, int length, int stepPoint, double stepValue);
void generateRandomNoise(double *signal, int length);
void generatePulseSignal(double *signal, int length, int pulseWidth, double pulseValue);

// Benchmark function prototype
void benchmark(char* name, double (*filter_func)(int, double*, double*, double), double* h, double *sample, char* sample_name);
void benchmarkCfir(char* name, double (*filter_func)(int, double*, double*, double**, double), double* h, double *sample, char* sample_name);
void benchmarkCfir2(double (*filter_func)(int, double*, double*, int*, double), double* h, double *sample, char* sample_name);
void benchmarkAll(double* h, double* sample, char* sample_name);

int main() {
    // Initialize filter coefficients and delay line
    double h[FILTER_LENGTH], w[FILTER_LENGTH];
    for (int i = 0; i < FILTER_LENGTH; i++) {
        h[i] = (rand()/RAND_MAX) * 2 - 1; // Simple coefficients for testing
        w[i] = 0; // Initialize delay line
    }

    // Test signals
    double sinusoidal[TEST_SIGNAL_LENGTH];
    double step[TEST_SIGNAL_LENGTH];
    double random[TEST_SIGNAL_LENGTH];
    double pulse[TEST_SIGNAL_LENGTH];

    // Generate test signals
    generateSinusoidal(sinusoidal, TEST_SIGNAL_LENGTH, 1.0, 100.0);
    generateStepFunction(step, TEST_SIGNAL_LENGTH, TEST_SIGNAL_LENGTH / 2, 1);
    generateRandomNoise(random, TEST_SIGNAL_LENGTH);
    generatePulseSignal(pulse, TEST_SIGNAL_LENGTH, 10, 1);

    // Run benchmarks for each signal type
    printf("Benchmarking with Sinusoidal Signal:\n");
    benchmarkAll(h, sinusoidal, "sinusoidal");
    printf("\n");

    printf("Benchmarking with Step Function Signal:\n");
    benchmarkAll(h, step, "step");
    printf("\n");

    printf("Benchmarking with Random Noise Signal:\n");
    benchmarkAll(h, random, "random");
    printf("\n");

    printf("Benchmarking with Pulse Signal:\n");
    benchmarkAll(h, pulse, "pulse");
    printf("\n");

    return 0;
}

void generateSinusoidal(double *signal, int length, double frequency, double samplingRate) {
    for (int i = 0; i < length; i++) {
        signal[i] = sin(2 * M_PI * frequency * i / samplingRate);
    }
}

void generateStepFunction(double *signal, int length, int stepPoint, double stepValue) {
    for (int i = 0; i < length; i++) {
        signal[i] = (i >= stepPoint) ? stepValue : 0;
    }
}

void generateRandomNoise(double *signal, int length) {
    for (int i = 0; i < length; i++) {
        signal[i] = rand() % 100;
    }
}

void generatePulseSignal(double *signal, int length, int pulseWidth, double pulseValue) {
    for (int i = 0; i < length; i++) {
        signal[i] = (i % pulseWidth == 0) ? pulseValue : 0;
    }
}

void benchmark(char* name, double (*filter_func)(int, double*, double*, double), double* h, double *sample, char* sample_name) {
    clock_t start, end;
    double w[FILTER_LENGTH] = {0};
    double total_time = 0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        start = clock();
        for (int i = 0; i < TEST_SIGNAL_LENGTH; i++) {
            filter_func(FILTER_LENGTH-1, h, w, sample[i]);
        }
        end = clock();
        total_time += ((double) (end - start)) / CLOCKS_PER_SEC;
    }

    double mean_time = total_time / ITERATIONS;
    printf("%s (%s): Mean execution time over %d iterations: %f seconds\n", name, sample_name, ITERATIONS, mean_time);
}

void benchmarkCfir(char* name, double (*filter_func)(int, double*, double*, double**, double), double* h, double *sample, char* sample_name) {
    clock_t start, end;
    double w[FILTER_LENGTH] = {0};
    double *p = w;
    double total_time = 0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        start = clock();
        for (int i = 0; i < TEST_SIGNAL_LENGTH; i++) {
            filter_func(FILTER_LENGTH-1, h, w, &p, sample[i]);
        }
        end = clock();
        total_time += ((double) (end - start)) / CLOCKS_PER_SEC;
    }

    double mean_time = total_time / ITERATIONS;
    printf("%s (%s): Mean execution time over %d iterations: %f seconds\n", name, sample_name, ITERATIONS, mean_time);
}

void benchmarkCfir2(double (*filter_func)(int, double*, double*, int*, double), double* h, double *sample, char* sample_name) {
    clock_t start, end;
    double w[FILTER_LENGTH] = {0};
    int q = 0;
    double total_time = 0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        start = clock();
        for (int i = 0; i < TEST_SIGNAL_LENGTH; i++) {
            filter_func(FILTER_LENGTH-1, h, w, &q, sample[i]);
        }
        end = clock();
        total_time += ((double) (end - start)) / CLOCKS_PER_SEC;
    }

    double mean_time = total_time / ITERATIONS;
    printf("cfir2_fixed (%s): Mean execution time over %d iterations: %f seconds\n", sample_name, ITERATIONS, mean_time);
}

void benchmarkAll(double* h, double* sample, char* sample_name) {
    benchmark("fir_fixed", fir, h, sample, sample_name);
    benchmark("fir2_fixed", fir2, h, sample, sample_name);
    benchmark("fir3_fixed", fir3, h, sample, sample_name);
    benchmarkCfir("cfir_fixed", cfir, h, sample, sample_name);
    benchmarkCfir("cfir1_fixed", cfir1, h, sample, sample_name);
    benchmarkCfir2(cfir2, h, sample, sample_name);
}