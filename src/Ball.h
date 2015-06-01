#pragma once
#include "DisplayableObject.h"
#include "Racket.h"

class Ball :
	public DisplayableObject
{
public:
	Ball(BaseEngine *pEngine, Racket *pRacket);
	~Ball(void);
	void Reset(void);
	void Draw(void);
	void DoUpdate(int iCurrentTime);
	void Serve(void);

	void Bounce(void) { m_dVelocity[1] *= -1; }
	void Track(int iX)
	{
		// Ball must be moving
		if (m_dVelocity[0] == 0 && m_dVelocity[1] == 0)
			m_iCurrentScreenX = iX;
	}

private:
	// Two-dimensional velocity vector {x,y} (0 = x, 1 = y)
	double m_dVelocity[2];
	Racket *m_pRacket;
	int m_iStartX, m_iStartY;
};

