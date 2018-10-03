#include <math.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "CGeneticHistogramme2.h"

CGeneticHistogramme2::CGeneticHistogramme2(CIndividuHistogramme2 **population, int taillePopulation, int step, int seuil) : CGenetic(population, taillePopulation) {
    oldScore = -1;
	_step =  step;
	_seuil = seuil;
}

void CGeneticHistogramme2::croiseIndividus(void) {
	int i, ir, max;
	
	i = 1;
	ir = getTaillePopulation() - 1;
	max = getTaillePopulation() / 2;
	while(i < max) {
		croise(i, i-1, ir);
		croise(i-1, i, ir-1);
		
		i += 2;
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
	int i, j;

	for(i=0;i<getTaillePopulation();i++) {
		double mult = 1;
		for(j=0;j<getTaillePopulation();j++) {
			if(i != j) {
				int dist = _population[i]->diff(_population[j]);
				
				if(dist < 10) {
					mult += (1 - ((double)dist) / 1000);
				}
			}
		}
		_population[i]->mulScore(mult);
	}
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
    if(_population[0]->getScore() < oldScore || oldScore == -1) {
        char fileName[255];
		
        sprintf(fileName, "images/img_%06d.png", _step);
        
        _population[0]->createImage(fileName);
        
        std::cout << "Meilleur " << _population[0]->getScore() <<  " (" << _step << ") en " << duree << " secondes" << std::endl;
        
        oldScore = _population[0]->getScore();
        _step++;
    }
}

bool CGeneticHistogramme2::isFini(void) const {
	return _population[0]->getScore() <= _seuil;
}	

void CGeneticHistogramme2::swapIndividus(int idx1, int idx2) {
	CIndividuHistogramme2 *tmp = _population[idx1];

	_population[idx1] = _population[idx2];
	_population[idx2] = tmp;
}
