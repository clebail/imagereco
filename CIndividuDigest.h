#ifndef __CINDIVIDUDIGEST_H__
#define __CINDIVIDUHISTOGRAMME_H__

#include <pHash.h>
#include "CIndividu.h"

class CIndividuDigest : public CIndividu<Digest *, double> {
public:
	CIndividuDigest(CIndividu* other);
	virtual void init(void);
    virtual void calculValue(void);
    virtual void calculScore(const Digest& reference);
	virtual void mute(void);
	virtual bool win(void) const;
private:
	void swapComposante(uchar *uc1, uchar *uc2);
};

#endif //__CINDIVIDUDIGEST_H__
