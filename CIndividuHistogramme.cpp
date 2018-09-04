#include <math.h>
#include "CIndividuHistogramme.h"

CIndividuHistogramme::CIndividuHistogramme(void) : CIndividu() {
    _value = new CHistogramme();
}

CIndividuHistogramme::CIndividuHistogramme(int width, int height, int pointSize) : CIndividu(width, height, pointSize) {
    _value = new CHistogramme();
}

void CIndividuHistogramme::init(void) {
	int i;
	
	for(i=0;i<getNbColor();i++) {
		_colors[i].r = (uchar)(rand() % 256);
		_colors[i].g = (uchar)(rand() % 256);
		_colors[i].b = (uchar)(rand() % 256);
	}
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

void CIndividuHistogramme::mute(void) {
	int seuil = rand() % getNbColor();
	
    if(rand() % 2) {
		_colors[seuil].r = (uchar)(rand() % 256);
	}
	
	if(rand() % 2) {
		_colors[seuil].g = (uchar)(rand() % 256);
	}
	
	if(rand() % 2) {
		_colors[seuil].b = (uchar)(rand() % 256);
	}
}

bool CIndividuHistogramme::win(void) const {
    return _score == 0;
}
