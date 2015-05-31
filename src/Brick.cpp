#include "header.h"
#include "templates.h"
#include "Brick.h"


Brick::Brick(BaseEngine *pEngine, int iX, int iY, int iWidth, int iHeight, unsigned int uiColour)
	: DisplayableObject(pEngine)
	, m_uiColour(uiColour)
{
	m_iCurrentScreenX = m_iPreviousScreenX = iX;
	m_iCurrentScreenY = m_iPreviousScreenY = iY;

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	m_iDrawWidth = iWidth;
	m_iDrawHeight = iHeight;

	SetVisible(true);
}


Brick::~Brick()
{
}


void Brick::Draw()
{
	m_pEngine->DrawRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		m_uiColour, GetEngine()->GetForeground());

	StoreLastScreenPositionAndUpdateRect();
}

