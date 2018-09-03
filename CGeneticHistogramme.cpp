#include <math.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "CGeneticHistogramme.h"

bool cmp(CIndividuHistogramme *i1, CIndividuHistogramme *i2) {
    return i1->getScore() < i2->getScore();
}

CGeneticHistogramme::CGeneticHistogramme(std::vector<CIndividuHistogramme *> population) : CGenetic(population) {
    oldScore = step =  0;
}

void CGeneticHistogramme::croiseIndividus(void) {
    int i, ir, max;
	
	i = 1;
	ir = _population.size() - 1;
	max = _population.size() / 2;
	
	while(i < max) {
        croise(i-1, i, ir);
		croise(i, i-1, ir-1);
		
		i+=2;
		ir-=2;
	}
}

void CGeneticHistogramme::triPopulation(void) {
    std::sort(_population.begin(), _population.end(), cmp);
}

void CGeneticHistogramme::croise(int i1, int i2, int ir) {
    _population[ir]->from(*_population[i1], *_population[i2]);
    _population[ir]->calculValue();
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
