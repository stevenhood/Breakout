#include "header.h"
#include "templates.h"
#include "StationaryObject.h"

StationaryObject::StationaryObject(BaseEngine *pEngine, char *szFileName, int iX, int iY)
	: DisplayableObject(pEngine)
{
	m_imgData.LoadImage(szFileName);

	m_iCurrentScreenX = m_iPreviousScreenX = iX;
	m_iCurrentScreenY = m_iPreviousScreenY = iY;

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	m_iDrawWidth = m_imgData.GetWidth();
	m_iDrawHeight = m_imgData.GetHeight();

	SetVisible(true);
}

StationaryObject::~StationaryObject(void)
{
}

void StationaryObject::Draw()
{
	m_imgData.RenderImageWithMask(
		GetEngine()->GetForeground(), 
		0, 0, 
		m_iCurrentScreenX, m_iCurrentScreenY, 
		m_iDrawWidth, m_iDrawHeight);

	StoreLastScreenPositionAndUpdateRect();
}
