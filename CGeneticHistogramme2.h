#ifndef __CGENETICHISTOGRAMME2_H__
#define __CGENETICHISTOGRAMME2_H__

#include "CGenetic.h"
#include "CIndividuHistogramme2.h"

class CGeneticHistogramme2 : public CGenetic<CIndividuHistogramme2 *,CHistogramme *> {
public:
	CGeneticHistogramme2(CIndividuHistogramme2 **population, int taillePopulation, int step, int seuil);
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
