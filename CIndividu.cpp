#include <iostream>
#include <stdio.h>
#include <string.h>
#include <gd.h>
#include "CHistogramme.h"
#include "CIndividu.h"

template <typename T>
CIndividu<T>::CIndividu(void) {
    _width = 0;
	_height= 0;
	_pointSize = 0;
	
	_nbColor = 0;
    
	_colors = 0;
}

template <typename T>
CIndividu<T>::CIndividu(int width, int height, int pointSize) {
	_width = width;
	_height= height;
	_pointSize = pointSize;
	
	_nbColor = ((width / pointSize) * (height / pointSize));
    
	_colors = new SColor[_nbColor];
}

template <typename T>
CIndividu<T>::CIndividu(const CIndividu& other) {
	int i;
	
	_width = other._width;
	_height= other._height;
	_pointSize =other._pointSize;
	
	_nbColor = other._nbColor;
	
	_colors = new SColor[_nbColor];
	for(i=0;i<_nbColor;i++) {
		_colors[i].r = other._colors[i].r;
		_colors[i].g = other._colors[i].g;
		_colors[i].b = other._colors[i].b;
	}
}

template <typename T>
CIndividu<T>::~CIndividu(void) {
	delete[] _colors;
}

template <typename T>
void CIndividu<T>::init(void) {
	int i;
	
	for(i=0;i<_nbColor;i++) {
		_colors[i].r = (uchar)(rand() % 256);
		_colors[i].g = (uchar)(rand() % 256);
		_colors[i].b = (uchar)(rand() % 256);
	}
}

template <typename T>
bool CIndividu<T>::win(void) const {
    return _score == 0;
}

template <typename T>
void CIndividu<T>::createImage(const char *fileName) const {
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

template <typename T>
int CIndividu<T>::getNbColor(void) {
    return _nbColor;
}

template <typename T>
void CIndividu<T>::calculValue(void) {
}

template <typename T>
void CIndividu<T>::calculScore(const T& reference) {
    _score = 0;
}

template <typename T>
void CIndividu<T>::from(const CIndividu& i1, const CIndividu& i2) {
    int seuil = rand() % _nbColor;
	
	memcpy(_colors, i1._colors, seuil * sizeof(SColor));
	memcpy(&_colors[seuil], &i2._colors[seuil], (_nbColor - seuil) * sizeof(SColor));
	
	seuil = rand() % _nbColor;
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

template <typename T>
int CIndividu<T>::getScore(void) const {
    return _score;
}

template class CIndividu<CHistogramme *>;
