#include "header.h"
#include "templates.h"
#include "Ball.h"
#include "Misc.h"

#define M_PI	3.14159265358979323846

Ball::Ball(BaseEngine* pEngine, int iStartX, int iStartY, Racket *pRacket)
	: DisplayableObject(pEngine)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = m_iStartX = iStartX;
	m_iCurrentScreenY = m_iPreviousScreenY = m_iStartY = iStartY;

	int iBallDiam = GetEngine()->GetScreenHeight() / 40;
	m_iDrawWidth = iBallDiam;
	m_iDrawHeight = iBallDiam;

	// Initial speed is zero
	m_dVelocity[0] = 0;
	m_dVelocity[1] = 0;

	SetVisible(true);

	// Store Racket for collision check
	m_pRacket = pRacket;
}


Ball::~Ball(void)
{
}


void Ball::Draw(void)
{
	GetEngine()->DrawScreenOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0xffffff);

	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.
	// This will then remove the object from the screen.
	StoreLastScreenPositionAndUpdateRect();
}


void Ball::DoUpdate(int iCurrentTime)
{
	m_iCurrentScreenX += m_dVelocity[0];
	m_iCurrentScreenY += m_dVelocity[1];

	// Bounce the ball off the left or right screen border
	if (m_iCurrentScreenX < 0) {
		// Change movement to opposite direction
		m_dVelocity[0] *= -1;
		m_iCurrentScreenX = 1;
	} else if (m_iCurrentScreenX >= GetEngine()->GetScreenWidth() - m_iDrawWidth) {
		m_dVelocity[0] *= -1;
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - m_iDrawWidth;
	}

	// Detect collision with racket
	if (IsCollideRect(this, m_pRacket)) {
		// Bounce ball off racket
		m_dVelocity[1] *= -1;
		m_iCurrentScreenY += m_dVelocity[1];
		// Pass some racket velocity to the ball
		m_dVelocity[0] += 0.5 * m_pRacket->GetVelocity();
	}/* else if (IsCollideRect(this, m_pPlayer2)) {
		m_dVelocity[0] *= -1;
		m_iCurrentScreenX += m_dVelocity[0];
		m_dVelocity[1] += 0.5 * m_pPlayer2->GetVelocity();
	}*/

	// Goal detection is in Pong.cpp

	RedrawObjects();
}


void Ball::Serve(void)
{
	if (m_dVelocity[1] != 0)
		return;

	// Random angle in radians (between 0 and 60 degrees)
	double dAngle = RandDouble(0, M_PI / 3.0);
	dAngle *= RandParity();

//	int iSide = RandParity();
	int iWidth = GetEngine()->GetScreenWidth();
	m_dVelocity[1] = -1 * iWidth / 48.0 * cos(dAngle);
	m_dVelocity[0] = iWidth / 48.0 * sin(dAngle);
}


// Sets the ball as stationary in the starting position
void Ball::Reset(void)
{
	m_iCurrentScreenX = m_iStartX;
	m_iCurrentScreenY = m_iStartY;
	// Set velocity to zero
	memset(m_dVelocity, 0, sizeof(m_dVelocity));
}
