#include "header.h"
#include "templates.h"
#include "Racket.h"


Racket::Racket(BaseEngine* pEngine, int iX, int iY, unsigned int uiColour)
	: DisplayableObject(pEngine)
{
	m_iCurrentScreenX = m_iPreviousScreenX = iX;
	m_iCurrentScreenY = m_iPreviousScreenY = iY;

	m_iDrawWidth = GetEngine()->GetScreenWidth() / 12;
	m_iDrawHeight = GetEngine()->GetScreenHeight() / 80;

	m_iVelocity = 0;
	m_uiColour = uiColour;

	SetVisible(true);
}


Racket::~Racket(void)
{
}


void Racket::Draw(void)
{
	GetEngine()->DrawScreenRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		m_uiColour);

	StoreLastScreenPositionAndUpdateRect();
}


void Racket::DoUpdate(int iCurrentTime)
{
	m_iCurrentScreenX += m_iVelocity;

	// Prevent the racket from moving off the left and right of the screen
	if (m_iCurrentScreenX < 0) {
		m_iCurrentScreenX = 0;
	} else if (m_iCurrentScreenX >= GetEngine()->GetScreenWidth() - m_iDrawWidth) {
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - m_iDrawWidth;
	}
}


void Racket::Left(void)
{
	m_iVelocity -= GetEngine()->GetScreenWidth() / 48;
}

void Racket::Right(void)
{
	m_iVelocity += GetEngine()->GetScreenWidth() / 48;
}


// Move the object in-place
void Racket::Move_ip(int iX, int iY)
{
	m_iCurrentScreenX += iX;
	m_iCurrentScreenY += iY;
}
