#define _USE_MATH_DEFINES // for M_PI
#include <cmath> // for cos, sin

#include "header.h"
#include "templates.h"
#include "Ball.h"
#include "Utils.h"

Ball::Ball(BaseEngine *pEngine, Racket *pRacket)
	: DisplayableObject(pEngine)
	, m_pRacket(pRacket)
{
	Reset();
	// Ball diameter
	int iDiameter = GetEngine()->GetScreenHeight() / 40;
	m_iDrawWidth = iDiameter;
	m_iDrawHeight = iDiameter;
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	SetVisible(true);
}

Ball::~Ball(void)
{
}

// Sets the ball as stationary in the starting position
void Ball::Reset(void)
{
	// Set velocity vector to zero
	memset(m_dVelocity, 0, sizeof(m_dVelocity));
	m_iCurrentScreenX = m_iPreviousScreenX = m_pRacket->GetXCentre();
	m_iCurrentScreenY = m_iPreviousScreenY = m_pRacket->GetYCentre() - 20;
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
	// Move with racket if not served yet
	if (m_dVelocity[0] == 0 && m_dVelocity[1] == 0)
		m_iCurrentScreenX = m_pRacket->GetXCentre();

	m_iCurrentScreenX += m_dVelocity[0];
	m_iCurrentScreenY += m_dVelocity[1];

	// Bounce the ball off the top screen border
	if (m_iCurrentScreenY < 0)
	{
		// Change movement to opposite direction
		m_dVelocity[1] *= -1;
		m_iCurrentScreenY = 1;
	}

	// Bounce the ball off the left or right screen border
	if (m_iCurrentScreenX < 0)
	{
		m_dVelocity[0] *= -1;
		m_iCurrentScreenX = 1;
	}
	else if (m_iCurrentScreenX >= GetEngine()->GetScreenWidth() - m_iDrawWidth)
	{
		m_dVelocity[0] *= -1;
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - m_iDrawWidth;
	}

	// Detect collision with racket
	if (IsCollideRect(this, m_pRacket))
	{
		// Bounce ball off racket
		Bounce();
		// Pass some racket velocity to the ball
		m_dVelocity[0] += 0.5 * m_pRacket->GetXVelocity();
	}

	// Brick collision detection is in Breakout.cpp

	RedrawObjects();
}

void Ball::Serve(void)
{
	// If ball is moving, cannot serve
	if (m_dVelocity[0] != 0 && m_dVelocity[1] != 0)
		return;

	// Random angle in radians (between 0 and 60 degrees)
	double dAngle = RandDouble(0, M_PI / 3.0) * RandParity();

	int iHeight = GetEngine()->GetScreenHeight();
	// Move upwards towards bricks (-1)
	m_dVelocity[1] = -1 * iHeight / 48.0 * cos(dAngle);
	m_dVelocity[0] = iHeight / 48.0 * sin(dAngle);
}
