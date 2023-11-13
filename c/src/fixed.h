#include <stdint.h>

// Define the fixed-point data type (e.g., 32-bit integer)
typedef int32_t fixed;

// Define the number of fractional bits
#define FRACTIONAL_BITS 16  // Example: 16 fractional bits

// Macro to convert from float to fixed-point
#define FLOAT_TO_FIXED(x) ((fixed)((x) * (1 << FRACTIONAL_BITS)))

// Macro to convert from fixed-point to float
#define FIXED_TO_FLOAT(x) ((float)(x) / (1 << FRACTIONAL_BITS))

// Macro for fixed-point multiplication
#define FIXED_MUL(a, b) (((fixed)(a) * (b)) >> FRACTIONAL_BITS)

// Macro for fixed-point addition
#define FIXED_ADD(a, b) ((fixed)(a) + (b))

// Macro for fixed-point subtraction
#define FIXED_SUB(a, b) ((fixed)(a) - (b))