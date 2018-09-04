#ifndef __CGENETICDIGEST_H__
#define __CGENETICDIGEST_H__

#include "CGenetic.h"
#include "CIndividuDigest.h"

class CGeneticDigest : public CGenetic<CIndividuDigest *,Digest *> {
public:
	CGeneticDigest(CIndividuDigest **population, int taillePopulation, int step);
    virtual void croiseIndividus(void);
    virtual void triPopulation(void);
	virtual void partagePopulation(void);
	int getStep(void);
protected:
	virtual void croise(int i1, int i2, int ir);
    virtual void actionBest(double duree);
private:
    double oldScore;
    int _step;
	
	void swapIndividus(int idx1, int idx2);
};

#endif //__CGENETICDIGEST_H__
