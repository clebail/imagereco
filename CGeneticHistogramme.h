#ifndef __CGENETICHISTOGRAMME_H__
#define __CGENETICHISTOGRAMME_H__

#include "CGenetic.h"
#include "CIndividuHistogramme.h"

class CGeneticHistogramme : public CGenetic<CIndividuHistogramme *,CHistogramme *> {
public:
	CGeneticHistogramme(CIndividuHistogramme **population, int taillePopulation, int step, int seuil);
    virtual void croiseIndividus(void);
    virtual void triPopulation(void);
	virtual void partagePopulation(void);
	int getStep(void);
protected:
	virtual void croise(int i1, int i2, int ir);
    virtual void actionBest(double duree);
	virtual bool isFini(void) const;
private:
    int oldScore;
    int _step;
	int _seuil;
	
	void swapIndividus(int idx1, int idx2);
};

#endif //__CGENETICHISTOGRAMME_H__
