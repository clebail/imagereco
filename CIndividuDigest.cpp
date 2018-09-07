#include <iostream>
#include "CIndividuDigest.h"
#include "CHistogramme.h"

CIndividuDigest::CIndividuDigest(CIndividu<CHistogramme *, int> *other) : CIndividu((CIndividu *)other) {
	_value = new Digest;
}

void CIndividuDigest::init(void) {
	int i, j;

	for(i=getNbColor()-1;i>=1;i--) {
		for(j=0;j<=i-1;j++) {
			if(rand() % 2) {
				uchar tmp = _colors[j+1].r;
				_colors[j+1].r = _colors[j].r;
				_colors[j].r = tmp;
			}
			
			if(rand() % 2) {
				uchar tmp = _colors[j+1].g;
				_colors[j+1].g = _colors[j].g;
				_colors[j].g = tmp;
			}
			
			if(rand() % 2) {
				uchar tmp = _colors[j+1].b;
				_colors[j+1].b = _colors[j].b;
				_colors[j].b = tmp;
			}
		}
	}
}

void CIndividuDigest::calculValue(void) {
	char fileName[256];
	unsigned long id = reinterpret_cast<unsigned long>(this);
	
	sprintf(fileName, "/tmp/img_%lu.png", id);
	createImage(fileName);
	
    ph_image_digest(fileName, 1.0, 1.0, *_value, 180);
}

void CIndividuDigest::calculScore(const Digest& reference) {
	calculValue();
	ph_crosscorr(reference, *_value, _score);
}

void CIndividuDigest::mute(void) {
	if(rand() % 2) {
		int i1 = rand() % getNbColor();
		int i2;
		do {
			i2 = rand() % getNbColor();
		}while(i2 == i1);
		
		uchar tmp = _colors[i1].r;
		_colors[i1].r = _colors[i2].r;
		_colors[i2].r = tmp;
	}
	
	if(rand() % 2) {
		int i1 = rand() % getNbColor();
		int i2;
		do {
			i2 = rand() % getNbColor();
		}while(i2 == i1);
		
		uchar tmp = _colors[i1].g;
		_colors[i1].g = _colors[i2].g;
		_colors[i2].g = tmp;
	}
	
	if(rand() % 2) {
		int i1 = rand() % getNbColor();
		int i2;
		do {
			i2 = rand() % getNbColor();
		}while(i2 == i1);
		
		uchar tmp = _colors[i1].b;
		_colors[i1].b = _colors[i2].b;
		_colors[i2].b = tmp;
	}
}

bool CIndividuDigest::win(void) const {
    return _score == 1.0;
}

void CIndividuDigest::from(const CIndividuDigest& i1, const CIndividuDigest& i2) {
	CHistogramme hRef;
	int seuilR = rand() % getNbColor();
	int seuilG = rand() % getNbColor();
	int seuilB = rand() % getNbColor();
	int teinteR[NB_TEINTE];
	int teinteG[NB_TEINTE];
	int teinteB[NB_TEINTE];
	int i, j;
	
	memset(teinteR, 0, sizeof(int) * NB_TEINTE);
    memset(teinteG, 0, sizeof(int) * NB_TEINTE);
    memset(teinteB, 0, sizeof(int) * NB_TEINTE);
	
	hRef.calcul(i1._colors, getNbColor());
	for(i=0;i<getNbColor();i++) {
		if(i < seuilR) {
			_colors[i].r = i1._colors[i].r;
			teinteR[_colors[i].r]++;
		} else {
			if(hRef.r()[i2._colors[i].r] > teinteR[i2._colors[i].r]) {
				_colors[i].r = i2._colors[i].r;
				teinteR[_colors[i].r]++;
			} else {
				bool fini = false;
				
				j = seuilR;
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
		
		if(i < seuilG) {
			_colors[i].g = i1._colors[i].g;
			teinteG[_colors[i].g]++;
		} else {
			if(hRef.g()[i2._colors[i].g] > teinteG[i2._colors[i].g]) {
				_colors[i].g = i2._colors[i].g;
				teinteG[_colors[i].g]++;
			} else {
				bool fini = false;
				
				j = seuilG;
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
		
		if(i < seuilB) {
			_colors[i].b = i1._colors[i].b;
			teinteB[_colors[i].b]++;
		} else {
			if(hRef.b()[i2._colors[i].b] > teinteB[i2._colors[i].b]) {
				_colors[i].b = i2._colors[i].b;
				teinteB[_colors[i].b]++;
			} else {
				bool fini = false;
				
				j = seuilB;
				do {
					if(hRef.b()[i1._colors[j].b] > teinteB[i1._colors[j].b]) {
						_colors[i].b = i1._colors[j].b;
						teinteB[_colors[i].b]++;
						fini = true;
					}
					j++;
					fini = fini || j == getNbColor();
				}while(!fini);
			}
		}
	}
	
	mute();
}

