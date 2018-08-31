#include "CGenetic.h"

typedef struct _SHistogramme {
	int r[256];
	int g[256];
	int b[256];
}SHistogramme;

class CGeneticHistogramme : public CGenetic<SHistogramme> {
public:
	CGeneticHistogramme(std::list<CIndividu> population);
	virtual void evalPopulation(const SHistogramme& reference) const;
	virtual void triPopulation(void);
	virtual void croiseIndividus(void);
protected:
	virtual void croise(int i1, int i2, int ir);
};
