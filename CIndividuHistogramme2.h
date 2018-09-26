#ifndef __CINDIVIDUHISTOGRAMME2_H__
#define __CINDIVIDUHISTOGRAMME2_H__

#include "CIndividuHistogramme.h"

class CIndividuHistogramme2 : public CIndividuHistogramme {
public:
    CIndividuHistogramme2(CIndividuHistogramme *other);;
	virtual void init(void);
    virtual void calculValue(void);
    virtual void calculScore(const CHistogramme& reference);
	virtual void mute(void);
	virtual bool win(void) const;
	virtual void from(const CIndividuHistogramme2& i1, const CIndividuHistogramme2& i2, int seuil1, int seuil2);
private:
	void swapComposante(uchar *c1, uchar *c2);
};

#endif //__CINDIVIDUHISTOGRAMME_H__
