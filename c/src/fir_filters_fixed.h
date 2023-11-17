#include "fixedptc.h"
#include "filter_utils.h"
#ifndef FIR_FILTERS_FIXED_H
#define FIR_FILTERS_FIXED_H

// Function declarations for FIR filters
fixedpt fir_fixed(int M, fixedpt *h, fixedpt *w, fixedpt x);
fixedpt fir2_fixed(int M, fixedpt *h, fixedpt *w, fixedpt x);
fixedpt fir3_fixed(int M, fixedpt *h, fixedpt *w, fixedpt x);
fixedpt cfir_fixed(int M, fixedpt *h, fixedpt *w, fixedpt **p, fixedpt x);
fixedpt cfir1_fixed(int M, fixedpt *h, fixedpt *w, fixedpt **p, fixedpt x);
fixedpt cfir2_fixed(int M, fixedpt *h, fixedpt *w, int *q, fixedpt x);

#endif // FIR_FILTERS_FIXED_H
