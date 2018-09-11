#ifndef __CGENETIC_H__
#define __CGENETIC_H__

#include <time.h>
#include "CIndividu.h"

template <typename T, typename E>
class CGenetic {
public:
	CGenetic(T *population, int taillePopulation);
	virtual ~CGenetic(void);
    void run(const E& reference, const time_t& debut);
    virtual void triPopulation(void) = 0;
    virtual void initPopulation(void);
	virtual void partagePopulation(void) = 0;
	virtual void evalPopulation(const E& reference);
	virtual void croiseIndividus(void) = 0;
	int getTaillePopulation(void);
	time_t getTime(void);
protected:
	T *_population;
	
	virtual void croise(int i1, int i2, int ir) = 0;
    virtual void actionBest(double duree) = 0;
private:
	int _taillePopulation;
	time_t _debut;
};

#endif //__CGENETIC_H__
