#ifndef __CINDIVIDUHISTOGRAMME_H__
#define __CINDIVIDUHISTOGRAMME_H__

#include "CIndividu.h"
#include "CHistogramme.h"

class CIndividuHistogramme : public CIndividu<CHistogramme *, int> {
public:
    CIndividuHistogramme(void);
	CIndividuHistogramme(CIndividuHistogramme *other);
    CIndividuHistogramme(int width, int height, int pointSize);
	virtual void init(void);
    virtual void calculValue(void);
    virtual void calculScore(const CHistogramme& reference);
	virtual void mute(void);
	virtual bool win(void) const;
};

#endif //__CINDIVIDUHISTOGRAMME_H__
