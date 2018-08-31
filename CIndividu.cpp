#include <stdio.h>
#include <gd.h>
#include "CIndividu.h"

CIndividu::CIndividu(int width, int height, int pointSize) {
	_width = width;
	_height= height;
	_pointSize = pointSize;
	
	_nbColor = ((width / pointSize) * (height / pointSize));
	
	_colors = new CColor[_nbColor];
}

CIndividu::CIndividu(const CIndividu& other) {
	int i;
	
	_width = other._width;
	_height= other._height;
	_pointSize =other._pointSize;
	
	_nbColor = other._nbColor;
	
	_colors = new CColor[_nbColor];
	for(i=0;i<_nbColor;i++) {
		_colors[i] = CColor(other._colors[i]);
	}
}

CIndividu::~CIndividu(void) {
	delete[] _colors;
}

void CIndividu::init(void) {
	int i;
	
	for(i=0;i<_nbColor;i++) {
		_colors[i].init();
	}
}

void CIndividu::createImage(const char *fileName) const {
	int x, y, i;
	gdImagePtr im = gdImageCreateTrueColor(_width, _height);
	FILE *out;
	
	for(y=i=0;y<_height;y+=_pointSize) {
		for(x=0;x<_width;x+=_pointSize,i++) {
			int c = gdImageColorAllocate(im, _colors[i].r(), _colors[i].g(), _colors[i].b());
			
			gdImageFilledRectangle(im, x, y, x+_pointSize, y+_pointSize, c);
		}
	}
	
	out = fopen(fileName, "w");
	gdImageJpeg(im, out, -1);
	
	fclose(out);
	gdImageDestroy(im);
}
