#ifndef __CINDIVIDUDIGEST_H__
#define __CINDIVIDUHISTOGRAMME_H__

#include <pHash.h>
#include "CIndividu.h"
#include "CHistogramme.h"

class CIndividuDigest : public CIndividu<Digest *, double> {
public:
	CIndividuDigest(CIndividu<CHistogramme *, int> *other);
	virtual void init(void);
    virtual void calculValue(void);
    virtual void calculScore(const Digest& reference);
	virtual void mute(void);
	virtual bool win(void) const;
	virtual void from(const CIndividuDigest& i1, const CIndividuDigest& i2);
};

#endif //__CINDIVIDUDIGEST_H__
