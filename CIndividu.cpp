#include <iostream>
#include <stdio.h>
#include <string.h>
#include <gd.h>
#include <pHash.h>
#include "CHistogramme.h"
#include "CIndividu.h"

#define COPY_STEP					4

template <typename T, typename E>
CIndividu<T, E>::CIndividu(void) {
	_width = 0;
	_height = 0;
	_pointSize = 0;
	
	_nbColor = 0;
    
	_colors = 0;
}

template <typename T, typename E>
CIndividu<T, E>::CIndividu(int width, int height, int pointSize) {
	_width = width;
	_height = height;
	_pointSize = pointSize;
	
	_nbColor = ((width / pointSize) * (height / pointSize));
    
	_colors = new SColor[_nbColor];
}

template <typename T, typename E>
CIndividu<T, E>::CIndividu(CIndividu *other) {
	int i;
	
	_width = other->_width;
	_height = other->_height;
	_pointSize = other->_pointSize;
	
	_nbColor = other->_nbColor;
	
	_colors = new SColor[_nbColor];
	for(i=0;i<_nbColor;i++) {
		_colors[i].r = other->_colors[i].r;
		_colors[i].g = other->_colors[i].g;
		_colors[i].b = other->_colors[i].b;
	}
}

template <typename T, typename E>
CIndividu<T, E>::~CIndividu(void) {
	delete[] _colors;
}

template <typename T, typename E>
void CIndividu<T, E>::init(void) {
}

template <typename T, typename E>
bool CIndividu<T, E>::win(void) const {
	return false;
}

template <typename T, typename E>
void CIndividu<T, E>::createImage(const char *fileName) const {
	int x, y, i;
	gdImagePtr im = gdImageCreateTrueColor(_width, _height);
	FILE *out;
	
	for(y=i=0;y<_height;y+=_pointSize) {
		for(x=0;x<_width;x+=_pointSize,i++) {
			int c = gdImageColorAllocate(im, _colors[i].r, _colors[i].g, _colors[i].b);
			
			gdImageFilledRectangle(im, x, y, x+_pointSize, y+_pointSize, c);
		}
	}
	
	out = fopen(fileName, "w");
	gdImageJpeg(im, out, -1);
	
	fclose(out);
	gdImageDestroy(im);
}

template <typename T, typename E>
int CIndividu<T, E>::getNbColor(void) {
    return _nbColor;
}

template <typename T, typename E>
void CIndividu<T, E>::calculValue(void) {
}

template <typename T, typename E>
void CIndividu<T, E>::calculScore(const T& reference) {
}

template <typename T, typename E>
void CIndividu<T, E>::from(const CIndividu& i1, const CIndividu& i2) {
    int i;
	const CIndividu *src = rand() % 2 ? &i1 : &i2;
	
	for(i=0;i<_nbColor;i+=COPY_STEP) {
		memcpy(&_colors[i], &src->_colors[i], COPY_STEP * sizeof(SColor));
		src = (src == &i1 ? &i2 : &i1);
	}
	
	mute();
}    

template <typename T, typename E>
E CIndividu<T, E>::getScore(void) const {
    return _score;
}

template class CIndividu<CHistogramme *, int>;
template class CIndividu<Digest *, double>;
