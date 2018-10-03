#include <math.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "CGeneticHistogramme.h"

CGeneticHistogramme::CGeneticHistogramme(CIndividuHistogramme **population, int taillePopulation, int step, int seuil) : CGenetic(population, taillePopulation) {
    oldScore = -1;
	_step =  step;
	_seuil = seuil;
}

void CGeneticHistogramme::croiseIndividus(void) {
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

void CGeneticHistogramme::triPopulation(void) {
	int i, j;

	for(i=getTaillePopulation()-1;i>=1;i--) {
		for(j=0;j<=i-1;j++) {
			if(_population[j+1]->getShareScore() < _population[j]->getShareScore()) {
				swapIndividus(j+1, j);
			}
		}
	}
}

void CGeneticHistogramme::partagePopulation(void) {
	int i, j;
	double *mult = new double[getTaillePopulation()];
	
	for(i=0;i<getTaillePopulation();i++) {
		mult[i] = 1.0;
	}

	for(i=0;i<getTaillePopulation();i++) {
		for(j=i+1;j<getTaillePopulation();j++) {
			int dist = _population[i]->diff(_population[j]);
				
			if(dist < 10) {
				double m = (1 - ((double)dist) / 1000);
				mult[i] += m;
				mult[j] += m;
			}
		}
		
		_population[i]->setShareScore(_population[i]->getScore() * mult[i]);
	}
	
	delete[] mult;
}

int CGeneticHistogramme::getStep(void) {
	return _step;
}

void CGeneticHistogramme::croise(int i1, int i2, int ir) {
    _population[ir]->from(*_population[i1], *_population[i2]);
}

void CGeneticHistogramme::actionBest(double duree) {
    if(_population[0]->getScore() != oldScore/* || oldScore == -1*/) {
        char fileName[255];
		
        sprintf(fileName, "images/img_%06d.png", _step);
        
        _population[0]->createImage(fileName);
        
        std::cout << "Meilleur " << _population[0]->getScore() <<  " (" << _step << ", " << _population[0]->getShareScore() << ") en " << duree << " secondes" << std::endl;
        
        oldScore = _population[0]->getScore();
        _step++;
    }
}

bool CGeneticHistogramme::isFini(void) const {
	return _population[0]->getScore() <= _seuil;
}	

void CGeneticHistogramme::swapIndividus(int idx1, int idx2) {
	CIndividuHistogramme *tmp = _population[idx1];

	_population[idx1] = _population[idx2];
	_population[idx2] = tmp;
}
