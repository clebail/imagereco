#include "CIndividu.h"

class CGenetic {
public:
	virtual ~CGenetic(void) {}
	virtual template<typename Type> void evalPopulation(CIndividu *population, Type reference) const = 0;
	virtual void triPopulation(CIndividu *population) const = 0;
	virtual int croiseIndividus(CIndividu *population const) = 0;
protected:
	virtual void croise(CIndividu *population, int i1, int i2, int ir) const = 0;
};
