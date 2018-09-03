#include <math.h>
#include "CIndividuHistogramme.h"

CIndividuHistogramme::CIndividuHistogramme(void) : CIndividu() {
    _value = new CHistogramme();
}

CIndividuHistogramme::CIndividuHistogramme(int width, int height, int pointSize) : CIndividu(width, height, pointSize) {
    _value = new CHistogramme();
}

void CIndividuHistogramme::calculValue(void) {
    _value->calcul(_colors, getNbColor());
}

void CIndividuHistogramme::calculScore(const CHistogramme& reference) {
    int i;
    
    _score = 0;
    calculValue();
    
    for(i=0;i<NB_TEINTE;i++) {
        _score += abs(reference.r()[i] - _value->r()[i]);
        _score += abs(reference.g()[i] - _value->g()[i]);
        _score += abs(reference.b()[i] - _value->b()[i]);
    }
}
