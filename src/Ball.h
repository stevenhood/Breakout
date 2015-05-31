#pragma once
#include <cmath> // for cos, sin
#include "DisplayableObject.h"
#include "Racket.h"

class Ball :
	public DisplayableObject
{
private:
	// Two-dimensional velocity vector {x,y}
	double m_dVelocity[2];
	Racket *m_pRacket;
	int m_iStartX;
	int m_iStartY;

public:
	Ball(BaseEngine* pEngine, int iStartX, int iStartY, Racket *pRacket);
	~Ball(void);
	void Draw(void);
	void DoUpdate(int iCurrentTime);
	void Serve(void);
	void Reset(void);
};

