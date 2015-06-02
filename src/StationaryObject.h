#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"

// A stationary image that is drawn to the foreground at the specified coordinates.
class StationaryObject :
	public DisplayableObject
{
public:
	StationaryObject(BaseEngine *pEngine, char *szFileName, int iX, int iY);
	~StationaryObject(void);
	void Draw();

protected:
	ImageData m_imgData;
};

