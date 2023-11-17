#include "fir_filters_fixed.h"

// FIR filter in direct form using fixedpt-point arithmetic
fixedpt fir_fixed(int M, fixedpt *h, fixedpt *w, fixedpt x) {
    int i;
    fixedpt y = 0;

    w[0] = x;

    for (i = 0; i <= M; i++)
        y += fixedpt_mul(h[i], w[i]);

    for (i = M; i >= 1; i--)
        w[i] = w[i - 1];

    return y;
}

// FIR filter in direct form using dot product and delay functions
fixedpt fir2_fixed(int M, fixedpt *h, fixedpt *w, fixedpt x) {
    fixedpt y;

    w[0] = x;

    y = dot_fixed(M, h, w);

    delay_fixed(M, w);

    return y;
}

// FIR filter emulating a DSP chip
fixedpt fir3_fixed(int M, fixedpt *h, fixedpt *w, fixedpt x) {
    int i;
    fixedpt y;

    w[0] = x;

    for (y = fixedpt_mul(h[M], w[M]), i = M - 1; i >= 0; i--) {
        w[i + 1] = w[i];
        y += fixedpt_mul(h[i], w[i]);
    }

    return y;
}

// FIR filter implemented with circular delay-line buffer
fixedpt cfir_fixed(int M, fixedpt *h, fixedpt *w, fixedpt **p, fixedpt x) {
    int i;
    fixedpt y;

    **p = x;

    for (y = 0, i = 0; i <= M; i++) {
        y += fixedpt_mul((*h++), *(*p)++);
        wrap_fixed(M, w, p);
    }

    (*p)--; 
    wrap_fixed(M, w, p);

    return y;
}

// FIR filter implemented with circular delay-line buffer
fixedpt cfir1_fixed(int M, fixedpt *h, fixedpt *w, fixedpt **p, fixedpt x) {
    int i;
    fixedpt y;

    *(*p)-- = x;
    wrap_fixed(M, w, p); 

    for (y = 0, h += M, i = M; i >= 0; i--) {
        y += fixedpt_mul((*h--), *(*p)--);
        wrap_fixed(M, w, p);
    }

    return y;
}

// FIR filter implemented with circular delay-line buffer
fixedpt cfir2_fixed(int M, fixedpt *h, fixedpt *w, int *q, fixedpt x) {
    int i;
    fixedpt y;

    w[*q] = x;

    for (y = 0, i = 0; i <= M; i++) {
        y = y + fixedpt_mul((*h++), w[(*q)++]);
        wrap2(M, q);
    }

    (*q)--; 
    wrap2(M, q);

    return y;
}
