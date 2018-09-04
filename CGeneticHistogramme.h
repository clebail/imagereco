#ifndef __CGENETICHISTOGRAMME_H__
#define __CGENETICHISTOGRAMME_H__

#include "CGenetic.h"
#include "CIndividuHistogramme.h"

class CGeneticHistogramme : public CGenetic<CIndividuHistogramme *,CHistogramme *> {
public:
	CGeneticHistogramme(CIndividuHistogramme **population, int taillePopulation);
    virtual void croiseIndividus(void);
    virtual void triPopulation(void);
protected:
	virtual void croise(int i1, int i2, int ir);
    virtual void actionBest(void);
private:
    int oldScore;
    int step;
	
	void swapIndividus(int idx1, int idx2);
};

#endif //__CGENETICHISTOGRAMME_H__
