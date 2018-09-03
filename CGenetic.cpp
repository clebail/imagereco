#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "CGenetic.h"
#include "CHistogramme.h"
#include "CIndividuHistogramme.h"

template <typename T, typename E>
CGenetic<T,E>::CGenetic(std::vector<T> population) {
	_population = population;
}

template <typename T, typename E>
CGenetic<T,E>::~CGenetic(void) {
}

template <typename T, typename E>
void CGenetic<T,E>::run(const E& reference) {
    bool fini = false;
    
    srand(time(NULL));

    initPopulation();
    evalPopulation(reference);
    triPopulation();
	
	do {
        croiseIndividus();
        evalPopulation(reference);
        triPopulation();
        
        actionBest();
		
		fini = _population.front()->win();
	}while(!fini);
}

template <typename T, typename E>
void CGenetic<T,E>::initPopulation(void) {
    unsigned i;
    
    for(i=0;i<_population.size();i++) {
        _population[i]->init();
    }
}

template <typename T, typename E>
void CGenetic<T,E>::evalPopulation(const E& reference) {
    unsigned i;
    
    for(i=0;i<_population.size();i++) {
        _population[i]->calculScore(*reference);
    }
}

template class CGenetic<CIndividuHistogramme *,CHistogramme *>;
