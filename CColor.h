#ifndef __CCOLOR_H__
#define __CCOLOR_H__

typedef unsigned char uchar;

class CColor {
public:
	CColor(void);
	CColor(const CColor& other);
    CColor(const int& r, const int& g, const int& b);
	uchar r(void) const;
	uchar g(void) const;
	uchar b(void) const;
	void init(void);
private:
	uchar _r;
	uchar _g;
	uchar _b;
};

#endif //__CCOLOR_H__
