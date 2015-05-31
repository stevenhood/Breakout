#pragma once
#include "DisplayableObject.h"

class Brick :
	public DisplayableObject
{
public:
	Brick(BaseEngine *pEngine, int iX, int iY, int iWidth, int iHeight, unsigned int uiColour);
	~Brick();
	void Draw();

private:
	unsigned int m_uiColour;
};

