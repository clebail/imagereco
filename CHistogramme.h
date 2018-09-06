#ifndef __CHISTOGRAMME_H__
#define __CHISTOGRAMME_H__

#include "commun.h"

#define NB_TEINTE       256

class CHistogramme {
public:
	CHistogramme(void);
    void calcul(SColor *colors, int nbColor);
    const int *r(void) const;
	const int *g(void) const;
	const int *b(void) const;
private:
    int _r[NB_TEINTE];
    int _g[NB_TEINTE];
    int _b[NB_TEINTE];
};

#endif //__CHISTOGRAMME_H__
