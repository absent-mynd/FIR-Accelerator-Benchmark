import numpy as np
from scipy.signal import firwin, firwin2, hilbert


def ideal_bandpass_filter(N, f1, f2, fs=2):
    return firwin(N, [f1, f2], pass_zero=False, fs=fs).tolist()


def ideal_differentiator(N, fs=2):
    # Use firwin2 with a frequency response that defines a differentiator
    freq = np.array([0, fs / 2])
    gain = np.array([0, np.pi * (fs / 2)])
    return firwin2(N, freq, gain, fs=fs).tolist()


def ideal_hilbert_transformer(N):
    # Create an array of N linearly spaced points
    t = np.arange(-N // 2 + 1, N // 2 + 1)

    # Hilbert transformer impulse response (h[n] = 2 / (pi * n) for n odd, 0 for n even)
    h = np.zeros(N)
    h[t % 2 == 1] = 2 / (np.pi * t[t % 2 == 1])

    return h.tolist()


def ideal_low_high_pass_filter(N, fc, is_highpass=False):
    if is_highpass:
        return firwin(N, fc, pass_zero=False, fs=2).tolist()
    else:
        return firwin(N, fc, pass_zero=True, fs=2).tolist()


N = 5  # Example length of the filter


# Bandpass Filter
print("Bandpass Filter:")
print(ideal_bandpass_filter(N, 0.2, 0.5))

# Differentiator
print("\nDifferentiator:")
print(ideal_differentiator(N))

# Hilbert Transformer
print("\nHilbert Transformer:")
print(ideal_hilbert_transformer(N))

# Lowpass Filter
print("\nLowpass Filter:")
print(ideal_low_high_pass_filter(N, 0.3))

# Highpass Filter
print("\nHighpass Filter:")
print(ideal_low_high_pass_filter(N, 0.3, is_highpass=True))
