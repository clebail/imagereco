#include <list>
#include "CIndividu.h"

template <typename T>
class CGenetic {
public:
	CGenetic(std::list<CIndividu> population);
	virtual ~CGenetic(void);
	virtual void evalPopulation(const T& reference) const = 0;
	virtual void triPopulation(void) = 0;
	virtual void croiseIndividus(void) = 0;
protected:
	std::list<CIndividu> _population;
	
	virtual void croise(int i1, int i2, int ir) = 0;
};
