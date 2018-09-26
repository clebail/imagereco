#include <string.h>
#include "CHistogramme.h"

CHistogramme::CHistogramme(void) {
	memset(_r, 0, sizeof(int) * NB_TEINTE);
    memset(_g, 0, sizeof(int) * NB_TEINTE);
    memset(_b, 0, sizeof(int) * NB_TEINTE);
	memset(_l, 0, sizeof(int) * NB_TEINTE);
	memset(_t, 0, sizeof(int) * NB_TEINTE);
}

void CHistogramme::calcul(SColor *colors, int nbColor) {
    int i;
    
    memset(_r, 0, sizeof(int) * NB_TEINTE);
    memset(_g, 0, sizeof(int) * NB_TEINTE);
    memset(_b, 0, sizeof(int) * NB_TEINTE);
	memset(_l, 0, sizeof(int) * NB_TEINTE);
	memset(_t, 0, sizeof(int) * NB_TEINTE);
    
    for(i=0;i<nbColor;i++) {
        _r[colors[i].r]++;
        _g[colors[i].g]++;
        _b[colors[i].b]++;
		
		_l[(int)(((double)colors[i].r) * 0.3 + ((double)colors[i].g) * 0.6 + ((double)colors[i].b) * 0.1)]++;
		
		_t[(colors[i].r + colors[i].g + colors[i].b)/3]++;
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

const int * CHistogramme::l(void) const {
    return _l;
}

const int * CHistogramme::t(void) const {
    return _t;
}
