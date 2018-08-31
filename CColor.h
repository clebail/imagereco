typedef unsigned char uchar;

class CColor {
public:
	CColor(void);
	CColor(const CColor& other);
	uchar r(void) const;
	uchar g(void) const;
	uchar b(void) const;
	void init(void);
private:
	uchar _r;
	uchar _g;
	uchar _b;
};
