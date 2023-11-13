import numpy as np


def print_expected_values(window_func, N, additional_param=None):
    if additional_param is not None:
        window = window_func(N, additional_param)
    else:
        window = window_func(N)

    print(f"Expected values for N={N}: {window}")


N = 5  # Example length of the window


# Hamming Window
print("Hamming Window:")
print_expected_values(np.hamming, N)

# Hanning Window
print("\nHanning Window:")
print_expected_values(np.hanning, N)

# Blackman Window
print("\nBlackman Window:")
print_expected_values(np.blackman, N)

# Kaiser Window (with beta = 5.0 as an example)
print("\nKaiser Window:")
print_expected_values(np.kaiser, N, 5.0)
