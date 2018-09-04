#ifndef __CGENETICHISTOGRAMME_H__
#define __CGENETICHISTOGRAMME_H__

#include "CGenetic.h"
#include "CIndividuHistogramme.h"

class CGeneticHistogramme : public CGenetic<CIndividuHistogramme *,CHistogramme *> {
public:
	CGeneticHistogramme(CIndividuHistogramme **population, int taillePopulation, int step);
    virtual void croiseIndividus(void);
    virtual void triPopulation(void);
	virtual void partagePopulation(void);
	int getStep(void);
protected:
	virtual void croise(int i1, int i2, int ir);
    virtual void actionBest(double duree);
private:
    int oldScore;
    int _step;
	
	void swapIndividus(int idx1, int idx2);
};

#endif //__CGENETICHISTOGRAMME_H__
