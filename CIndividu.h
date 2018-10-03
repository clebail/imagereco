#ifndef __CINDIVIDU_H__
#define __CINDIVIDU_H__

#include "commun.h"

template <typename T, typename E>
class CIndividu {
public:
	CIndividu(void);
	CIndividu(int width, int height, int pointSize);
	CIndividu(CIndividu * other);
	~CIndividu(void);
	virtual void init(void);
    virtual bool win(void) const;
	void createImage(const char *fileName) const;
    int getNbColor(void);
    virtual void calculValue(void);
	virtual E diff(CIndividu *other);
    virtual void calculScore(const T& reference);
    virtual void from(const CIndividu& i1, const CIndividu& i2);
    E getScore(void) const;
	E getShareScore(void) const;
	void setShareScore(const E& shareScore); 
	virtual void mute(void) = 0;
	int getWidth(void);
	int getHeight(void);
	int getPointSize(void);
	T getValue(void) const;
protected:
    SColor *_colors;
    E _score;
	E _shareScore;
	T _value;
private:
	int _nbColor;
	int _width;
	int _height;
	int _pointSize;
};

#endif //__CINDIVIDU_H__
