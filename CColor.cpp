#include <stdlib.h>
#include <time.h>
#include "CColor.h"

CColor::CColor(void) {
	srand(time(NULL));
	init();
}

CColor::CColor(const CColor& other) {
	srand(time(NULL));
	
	_r = other._r;
	_g = other._g;
	_b = other._b;
}

uchar CColor::r(void) const {
	return _r;
}

uchar CColor::g(void) const {
	return _g;
}

uchar CColor::b(void) const {
	return _b;
}

void CColor::init(void) {
	_r = (uchar)(rand() % 256);
	_g = (uchar)(rand() % 256);
	_b = (uchar)(rand() % 256);
}
