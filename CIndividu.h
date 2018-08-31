#include "CColor.h"

class CIndividu {
public:
	CIndividu(int width, int height, int pointSize);
	CIndividu(const CIndividu& other);
	~CIndividu(void);
	virtual void init(void);
	void createImage(const char *fileName) const;
private:
	CColor *_colors;
	int _nbColor;
	int _width;
	int _height;
	int _pointSize;
};
