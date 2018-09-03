#ifndef __CINDIVIDUHISTOGRAMME_H__
#define __CINDIVIDUHISTOGRAMME_H__

#include "CIndividu.h"
#include "CHistogramme.h"

class CIndividuHistogramme : public CIndividu<CHistogramme *> {
public:
    CIndividuHistogramme(void);
    CIndividuHistogramme(int width, int height, int pointSize);
    virtual void calculValue(void);
    virtual void calculScore(const CHistogramme& reference);
};

#endif //__CINDIVIDUHISTOGRAMME_H__
