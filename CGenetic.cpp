#include <stdlib.h>
#include <time.h>
#include <pHash.h>
#include <iostream>
#include "CGenetic.h"
#include "CHistogramme.h"
#include "CIndividuHistogramme.h"
#include "CIndividuHistogramme2.h"
#include "CIndividuDigest.h"

template <typename T, typename E>
CGenetic<T,E>::CGenetic(T *population, int taillePopulation) {
	_population = population;
	_taillePopulation = taillePopulation;
}

template <typename T, typename E>
CGenetic<T,E>::~CGenetic(void) {
}

template <typename T, typename E>
void CGenetic<T,E>::run(const E& reference, const time_t& debut) {
    _debut = debut;
	
    srand(time(NULL));

	//std::cout << "init" << std::endl;
    initPopulation();
	//std::cout << "eval" << std::endl;
    evalPopulation(reference);
	//std::cout << "tri" << std::endl;
    triPopulation();
	
	do {
		//std::cout << "croise" << std::endl;
		croiseIndividus();
		//std::cout << "eval" << std::endl;
		evalPopulation(reference);
		//std::cout << "partage" << std::endl;
		partagePopulation();
		//std::cout << "tri" << std::endl;
        triPopulation();
        
        actionBest(difftime(time(NULL), _debut));
	}while(!isFini());
}

template <typename T, typename E>
int CGenetic<T,E>::getTaillePopulation(void) {
	return _taillePopulation;
}

template <typename T, typename E>
void CGenetic<T,E>::initPopulation(void) {
    int i;
    
    for(i=0;i<_taillePopulation;i++) {
        _population[i]->init();
    }
}

template <typename T, typename E>
void CGenetic<T,E>::evalPopulation(const E& reference) {
    int i;
    
    for(i=0;i<_taillePopulation;i++) {
        _population[i]->calculScore(*reference);
    }
}

template <typename T, typename E>
time_t CGenetic<T,E>::getTime(void) {
	return time(NULL);
}

template class CGenetic<CIndividuHistogramme *,CHistogramme *>;
template class CGenetic<CIndividuHistogramme2 *,CHistogramme *>;
template class CGenetic<CIndividuDigest *,Digest *>;
