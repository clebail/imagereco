#include <math.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "CGeneticHistogramme2.h"

CGeneticHistogramme2::CGeneticHistogramme2(CIndividuHistogramme2 **population, int taillePopulation, int step, int seuil) : CGenetic(population, taillePopulation, seuil) {
    oldScore = 0;
	_step =  step;
}

void CGeneticHistogramme2::croiseIndividus(void) {
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

void CGeneticHistogramme2::triPopulation(void) {
	int i, j;

	for(i=getTaillePopulation()-1;i>=1;i--) {
		for(j=0;j<=i-1;j++) {
			if(_population[j+1]->getScore() < _population[j]->getScore()) {
				swapIndividus(j+1, j);
			}
		}
	}
}

void CGeneticHistogramme2::partagePopulation(void) {
}

int CGeneticHistogramme2::getStep(void) {
	return _step;
}

void CGeneticHistogramme2::croise(int i1, int i2, int ir) {
	int seuil1 = rand() % _population[i1]->getNbColor(); 
	int seuil2 = rand() % _population[i1]->getNbColor();
	
    _population[ir]->from(*_population[i1], *_population[i2], seuil1, seuil2);
}

void CGeneticHistogramme2::actionBest(double duree) {
    if(_population[0]->getScore() != oldScore) {
        char fileName[255];
		
        sprintf(fileName, "images/img_%06d.png", _step);
        
        _population[0]->createImage(fileName);
        
        std::cout << "Meilleur " << _population[0]->getScore() <<  " (" << _step << ") en " << duree << " secondes" << std::endl;
        
        oldScore = _population[0]->getScore();
        _step++;
    }
}

void CGeneticHistogramme2::swapIndividus(int idx1, int idx2) {
	CIndividuHistogramme2 *tmp = _population[idx1];

	_population[idx1] = _population[idx2];
	_population[idx2] = tmp;
}
