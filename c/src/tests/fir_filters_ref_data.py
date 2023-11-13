import numpy as np


def calculate_fir_output(h, x):
    return np.convolve(h, x, mode='full')


# Filter coefficients
h = np.array([0.1, 0.2, 0.3, 0.4])

# Generate a sinusoidal input signal
t = np.arange(0, 1.0, 0.1)  # Time vector
f = 2  # Frequency in Hz
x = np.sin(2 * np.pi * f * t)  # Sinusoidal input

# Calculate expected output
expected_output = calculate_fir_output(h, x)

print("Input signal:", x.tolist())
print("Expected output:", expected_output.tolist())
