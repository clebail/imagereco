#include <math.h>
#include <string.h>
#include "CIndividuHistogramme2.h"

CIndividuHistogramme2::CIndividuHistogramme2(CIndividuHistogramme *other) : CIndividuHistogramme(other) {
	_value = new CHistogramme();
}

void CIndividuHistogramme2::init(void) {
	int i;

	for(i=getNbColor()-1;i>=1;i--) {
		swapComposante(&_colors[rand() % (i + 1)].r, &_colors[i].r);
		swapComposante(&_colors[rand() % (i + 1)].g, &_colors[i].g);
		swapComposante(&_colors[rand() % (i + 1)].b, &_colors[i].b);
	}
}

void CIndividuHistogramme2::calculValue(void) {
    _value->calcul(_colors, getNbColor());
}

void CIndividuHistogramme2::calculScore(const CHistogramme& reference) {
    int i;
    
    _score = 0;
    calculValue();
    
    for(i=0;i<NB_TEINTE;i++) {
        _score += abs(reference.l()[i] - _value->l()[i]);
        //_score += abs(reference.t()[i] - _value->t()[i]);
    }
}

void CIndividuHistogramme2::mute(void) {
	int i1, i2, nb;
	
	/*if(rand() % 2) {
		i1 = rand() % getNbColor();
		do {
			i2 = rand() % getNbColor();
		}while(i2 < i1);
		
		while(i1 < i2) {
			swapComposante(&_colors[i1].r, &_colors[i2].r);
			
			i1++;
			i2--;
		}
	}else {*/
		nb = rand() % (int)(getNbColor() * 0.3);
		while(nb) {
			i1 = rand() % getNbColor();
			do {
				i2 = rand() % getNbColor();
			}while(i2 == i1);
			
			swapComposante(&_colors[i1].r, &_colors[i2].r);
			nb--;
		}
	//}
	
	/*if(rand() % 2) {
		i1 = rand() % getNbColor();
		do {
			i2 = rand() % getNbColor();
		}while(i2 < i1);
		
		while(i1 < i2) {
			swapComposante(&_colors[i1].g, &_colors[i2].g);
			
			i1++;
			i2--;
		}
	} else {*/
		nb = rand() % (int)(getNbColor() * 0.6);
		while(nb) {
			i1 = rand() % getNbColor();
			do {
				i2 = rand() % getNbColor();
			}while(i2 == i1);
			
			swapComposante(&_colors[i1].g, &_colors[i2].g);
			nb--;
		}
	//}
	
	/*if(rand() % 2) {
		i1 = rand() % getNbColor() ;
		do {
			i2 = rand() % getNbColor();
		}while(i2 < i1);
		
		while(i1 < i2) {
			swapComposante(&_colors[i1].b, &_colors[i2].b);
			
			i1++;
			i2--;
		}
	} else {*/
		nb = rand() % (int)(getNbColor() * 0.1);
		while(nb) {
			i1 = rand() % getNbColor();
			do {
				i2 = rand() % getNbColor();
			}while(i2 == i1);
			
			swapComposante(&_colors[i1].b, &_colors[i2].b);
			nb--;
		}
	//}
}

bool CIndividuHistogramme2::win(void) const {
    return false;
}

void CIndividuHistogramme2::from(const CIndividuHistogramme2& i1, const CIndividuHistogramme2& i2, int seuil1, int seuil2) {
	CHistogramme hRef;
	int teinteR[NB_TEINTE];
	int teinteG[NB_TEINTE];
	int i, j;
	
	memset(teinteR, 0, sizeof(int) * NB_TEINTE);
    memset(teinteG, 0, sizeof(int) * NB_TEINTE);
	
	hRef.calcul(i1._colors, getNbColor());
	for(i=0;i<getNbColor();i++) {
		if(i < seuil1) {
			_colors[i].r = i1._colors[i].r;
			teinteR[_colors[i].r]++;
		} else {
			if(hRef.r()[i2._colors[i].r] > teinteR[i2._colors[i].r]) {
				_colors[i].r = i2._colors[i].r;
				teinteR[_colors[i].r]++;
			} else {
				bool fini = false;
				
				j = seuil1;
				do {
					if(hRef.r()[i1._colors[j].r] > teinteR[i1._colors[j].r]) {
						_colors[i].r = i1._colors[j].r;
						teinteR[_colors[i].r]++;
						fini = true;
					}
					j++;
					fini = fini || j == getNbColor();
				}while(!fini);
			}
		}
		
		if(i < seuil2) {
			_colors[i].g = i1._colors[i].g;
			teinteG[_colors[i].g]++;
		} else {
			if(hRef.g()[i2._colors[i].g] > teinteG[i2._colors[i].g]) {
				_colors[i].g = i2._colors[i].g;
				teinteG[_colors[i].g]++;
			} else {
				bool fini = false;
				
				j = seuil2;
				do {
					if(hRef.g()[i1._colors[j].g] > teinteG[i1._colors[j].g]) {
						_colors[i].g = i1._colors[j].g;
						teinteG[_colors[i].g]++;
						fini = true;
					}
					j++;
					fini = fini || j == getNbColor();
				}while(!fini);
			}
		}
		
		_colors[i].b = i1._colors[i].b;
	}
	
	mute();
}

void CIndividuHistogramme2::swapComposante(uchar *c1, uchar *c2) {
	uchar tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

