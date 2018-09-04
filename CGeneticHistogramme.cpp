#include <math.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "CGeneticHistogramme.h"

CGeneticHistogramme::CGeneticHistogramme(CIndividuHistogramme **population, int taillePopulation) : CGenetic(population, taillePopulation) {
    oldScore = step =  0;
}

void CGeneticHistogramme::croiseIndividus(void) {
    int i, ir, max;
	
	i = 1;
	ir = getTaillePopulation() - 1;
	max = getTaillePopulation() / 2;
	
	while(i < max) {
        croise(i-1, i, ir);
		croise(i, i-1, ir-1);
		
		i+=2;
		ir-=2;
	}
}

void CGeneticHistogramme::triPopulation(void) {
	int i, j;

	for(i=getTaillePopulation()-1;i>=1;i--) {
		for(j=0;j<=i-1;j++) {
			if(_population[j+1]->getScore() < _population[j]->getScore()) {
				swapIndividus(j+1, j);
			}
		}
	}
}

void CGeneticHistogramme::croise(int i1, int i2, int ir) {
    _population[ir]->from(*_population[i1], *_population[i2]);
}

void CGeneticHistogramme::actionBest(void) {
    if(_population[0]->getScore() != oldScore) {
        char fileName[255];
		
        sprintf(fileName, "images/img_%06d.jpg", step);
        
        _population[0]->createImage(fileName);
        
        std::cout << "Meilleur " << _population[0]->getScore() << std::endl;
        
        oldScore = _population[0]->getScore();
        step++;
    }
}

void CGeneticHistogramme::swapIndividus(int idx1, int idx2) {
	CIndividuHistogramme *tmp = _population[idx1];

	_population[idx1] = _population[idx2];
	_population[idx2] = tmp;
}
