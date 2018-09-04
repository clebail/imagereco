#ifndef __CINDIVIDU_H__
#define __CINDIVIDU_H__

#include "commun.h"

template <typename T>
class CIndividu {
public:
    CIndividu(void);
	CIndividu(int width, int height, int pointSize);
	CIndividu(const CIndividu& other);
	~CIndividu(void);
	virtual void init(void);
    virtual bool win(void) const;
	void createImage(const char *fileName) const;
    int getNbColor(void);
    virtual void calculValue(void);
    virtual void calculScore(const T& reference);
    void from(const CIndividu& i1, const CIndividu& i2);
    int getScore(void) const;
protected:
    SColor *_colors;
    int _score;
    T _value;
private:
	int _nbColor;
	int _width;
	int _height;
	int _pointSize;
};

#endif //__CINDIVIDU_H__
