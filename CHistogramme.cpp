#include <string.h>
#include "CHistogramme.h"

void CHistogramme::calcul(SColor *colors, int nbColor) {
    int i;
    
    memset(_r, 0, sizeof(int) * NB_TEINTE);
    memset(_g, 0, sizeof(int) * NB_TEINTE);
    memset(_b, 0, sizeof(int) * NB_TEINTE);
    
    for(i=0;i<nbColor;i++) {
        _r[colors[i].r]++;
        _g[colors[i].g]++;
        _b[colors[i].b]++;
    }
}

const int * CHistogramme::r(void) const {
    return _r;
}

const int * CHistogramme::g(void) const {
    return _g;
}

const int * CHistogramme::b(void) const {
    return _b;
}
