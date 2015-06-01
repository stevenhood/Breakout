#pragma once
#include "DisplayableObject.h"

class Racket :
	public DisplayableObject
{
public:
	Racket(BaseEngine *pEngine, int iX, int iY, unsigned int uiColour);
	~Racket(void);
	void Draw(void);
	void DoUpdate(int iCurrentTime);
	void Left(void);
	void Right(void);

	// Allows the racket to be moved using the mouse
	void Track(int iX) { m_iCurrentScreenX = iX; }

	int GetXVelocity(void) { return m_iXVelocity; }

private:
	int m_iXVelocity;
	unsigned int m_uiColour;
};

