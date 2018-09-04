#include <math.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "CGeneticDigest.h"

CGeneticDigest::CGeneticDigest(CIndividuDigest **population, int taillePopulation, int step) : CGenetic(population, taillePopulation) {
    oldScore = 0.0;
	_step =  step;
}

void CGeneticDigest::croiseIndividus(void) {
   int i1, i2, ir, max, nb;
	
	ir = getTaillePopulation() - 1;
	max = getTaillePopulation() / 2;
	nb = 0;
	while(nb < max) {
		i1 = rand() % max;
		do {
			i2 = rand() % max;
		}while(i2 == i1);
		
		croise(i1, i2, ir);
		croise(i2, i1, ir-1);
		
		nb += 2;
		ir -= 2;
	}
}

void CGeneticDigest::triPopulation(void) {
	int i, j;

	for(i=getTaillePopulation()-1;i>=1;i--) {
		for(j=0;j<=i-1;j++) {
			if(_population[j+1]->getScore() > _population[j]->getScore()) {
				swapIndividus(j+1, j);
			}
		}
	}
}

void CGeneticDigest::partagePopulation(void) {
}

int CGeneticDigest::getStep(void) {
	return _step;
}

void CGeneticDigest::croise(int i1, int i2, int ir) {
    _population[ir]->from(*_population[i1], *_population[i2]);
}

void CGeneticDigest::actionBest(double duree) {
    if(_population[0]->getScore() != oldScore) {
        char fileName[255];
		
        sprintf(fileName, "images/img_%06d.jpg", _step);
        
        _population[0]->createImage(fileName);
        
        std::cout << "Meilleur " << _population[0]->getScore() <<  " (" << _step << ") en " << duree << " secondes" << std::endl;
        
        oldScore = _population[0]->getScore();
        _step++;
    }
}

void CGeneticDigest::swapIndividus(int idx1, int idx2) {
	CIndividuDigest *tmp = _population[idx1];

	_population[idx1] = _population[idx2];
	_population[idx2] = tmp;
}
