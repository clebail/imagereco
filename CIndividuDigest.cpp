#include "CIndividuDigest.h"

CIndividuDigest::CIndividuDigest(CIndividu * other) : CIndividu(other) {
}

void CIndividuDigest::init(void) {
	
}

void CIndividuDigest::calculValue(void) {
	char fileName[256];
	unsigned long id = reinterpret_cast<unsigned long>(this);
	
	sprintf(fileName, "/tmp/img_%lu.jpg", id);
	createImage(fileName);
	
    ph_image_digest(fileName, 1.0, 1.0, *_value, 180);
}

void CIndividuDigest::calculScore(const Digest& reference) {
	ph_crosscorr(reference, *_value, _score);
}

void CIndividuDigest::mute(void) {
	if(rand() % 2) {
		int i1, i2;
		
		i1 = rand() % getNbColor();
		do {
			i2 = rand() % getNbColor();
		}while(i2 == i1);
		
		swapComposante(&_colors[i1].r, &_colors[i2].r);
	}
	
	if(rand() % 2) {
		int i1, i2;
		
		i1 = rand() % getNbColor();
		do {
			i2 = rand() % getNbColor();
		}while(i2 == i1);
		
		swapComposante(&_colors[i1].g, &_colors[i2].g);
	}
	
	if(rand() % 2) {
		int i1, i2;
		
		i1 = rand() % getNbColor();
		do {
			i2 = rand() % getNbColor();
		}while(i2 == i1);
		
		swapComposante(&_colors[i1].b, &_colors[i2].b);
	}
}

bool CIndividuDigest::win(void) const {
    return _score == 1.0;
}

void CIndividuDigest::swapComposante(uchar *uc1, uchar *uc2) {
	uchar tmp = *uc1;
	*uc1 = *uc2;
	*uc2 = tmp;
}
