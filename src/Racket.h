#pragma once
#include "DisplayableObject.h"

class Racket :
	public DisplayableObject
{
public:
	int m_iVelocity;
	unsigned int m_uiColour;

	Racket(BaseEngine* pEngine, int iX, int iY, unsigned int uiColour);
	~Racket(void);
	void Draw(void);
	void DoUpdate(int iCurrentTime);
	void Left(void);
	void Right(void);
	void Move_ip(int iX, int iY);

	int GetVelocity(void) { return m_iVelocity; }
};

