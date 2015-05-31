#include "header.h"
#include "templates.h"
#include "Breakout.h"
#include "Utils.h"

const int Breakout::m_iMaxNumObjects = 150;
const int Breakout::m_iNumRows = 8;
const int Breakout::m_iNumCols = 10;
const int Breakout::m_iMaxNumLives = 3;


Breakout::Breakout(void)
	: BaseEngine(m_iMaxNumObjects)
	, m_State(stateInit)
{
	Reset();
}


Breakout::~Breakout(void)
{
	// See case SDLK_ESCAPE in KeyDown
}


void Breakout::Reset(void)
{
	m_iNumLives = m_iMaxNumLives;
	m_iScore = 0;
}


int Breakout::InitialiseObjects()
{
	DrawableObjectsChanged();
	DestroyOldObjects();
	m_ppDisplayableObjects = new DisplayableObject*[m_iMaxNumObjects];

	// The LAST entry has to be NULL. This is used to work out where the end of the array is.
	for (int i = 0; i < m_iMaxNumObjects; i++)
		m_ppDisplayableObjects[i] = NULL;

	m_ppDisplayableObjects[0] = m_pRacket = new Racket(this, GetScreenWidth() * 0.5, GetScreenHeight() * 0.925, 0xffffff);
	m_ppDisplayableObjects[1] = m_pBall = new Ball(this, GetScreenWidth() * 0.5, GetScreenHeight() * 0.5, m_pRacket);
	m_iBricksStartIndex = 2;
	int iLastIndex = SetupBricks(m_iBricksStartIndex);
	m_ppDisplayableObjects[iLastIndex] = NULL;

	switch (m_State)
	{
	case stateInit:
		break;

	case stateEnd:
		break;

	case stateMain:
		break;
	}

	return 0;
}


int Breakout::SetupBricks(int iIndex)
{
	unsigned int auiColours[] = { 0xff0000, 0x00ff00, 0x00000ff };
	int iNumColours = 3;
	// Offset from left of screen
	int iLeftOffset = 10;
	int iTopOffset = 30;

	int iColour = 0;
	int iOffset = 10;
	int iWidth = 60;
	int iHeight = 15;

	for (int iRow = 0; iRow < m_iNumRows; iRow++)
	{
		int iY = (iHeight + iOffset) * iRow + iTopOffset;
		for (int iCol = 0; iCol < m_iNumCols; iCol++)
		{
			int iX = (iWidth + iOffset) * iCol + iLeftOffset;
			//printf("iX: %d, iY: %d\n", iX, iY);
			m_ppDisplayableObjects[iIndex++] = new Brick(this, iX, iY, iWidth, iHeight, auiColours[iColour]);
			iColour = (iColour + 1) % iNumColours;
		}
	}

	// First unused index
	return iIndex;
}


void Breakout::SetupBackgroundBuffer()
{
	FillBackground(0x000000);
}


void Breakout::GameAction()
{
	// If too early to act then do nothing
	if (!TimeToAct())
		return;
	// Don't act for another 30 ticks (approx. 30fps)
	SetTimeToAct(30);

	CheckBrickCollisions();

	// Detect ball passing bottom of screen
	if (m_pBall->GetYCentre() > GetScreenHeight())
	{
		m_iNumLives--;
		if (m_iNumLives <= 0) {
			GameOver();
		} else {
			m_pBall->Reset();
			printf("Life lost: %d remaining\n", m_iNumLives);
		}
	}

	// Redraw screen
	Redraw(true);

	// Tell all objects to update themselves; call GameRender() on each.
	UpdateAllObjects(GetTime());
}


void Breakout::GameOver(void)
{
	// TODO
}


/* Draw text labels */
void Breakout::DrawStrings(void)
{
	CopyBackgroundPixels(0, GetScreenHeight() * 0.9, GetScreenWidth(), GetScreenHeight() * 0.1);

	char str[32];
	// Render the score
	sprintf(str, "Score %d", m_iScore);
	DrawScreenString(GetScreenWidth() * 0.02, GetScreenHeight() * 0.95, str, 0xffffff, NULL);

	// Render the number of lives
	sprintf(str, "Lives %d", m_iNumLives);
	DrawScreenString(GetScreenWidth() * 0.80, GetScreenHeight() * 0.95, str, 0xffffff, NULL);

	SetNextUpdateRect(0, GetScreenHeight() * 0.9, GetScreenWidth(), GetScreenHeight() * 0.1);
}


void Breakout::CheckBrickCollisions(void)
{
	// TODO what if the whole array is full?
	for (int i = m_iBricksStartIndex; m_ppDisplayableObjects[i] != NULL; i++)
	{
		if (IsCollideRect(m_ppDisplayableObjects[i], m_pBall))
		{
			delete m_ppDisplayableObjects[i];
			m_ppDisplayableObjects[i] = NULL;
			m_iScore += 10;
			m_pBall->Bounce();
			break;
		}
	}

	// Clean up any NULLs in between object pointers
	MoveNullsToEnd(m_ppDisplayableObjects, m_iMaxNumObjects);
}


void Breakout::KeyDown(int iKeyCode)
{
	switch (iKeyCode)
	{
	case SDLK_LEFT: m_pRacket->Left(); break;
	case SDLK_RIGHT: m_pRacket->Right(); break;
	case SDLK_SPACE: m_pBall->Serve(); break;

	case SDLK_ESCAPE: // End program when escape is pressed
		// Free array beforehand
		DrawableObjectsChanged();
		DestroyOldObjects();
		SetExitWithCode(0);
		break;
	default:
		break;
	}
}


void Breakout::KeyUp(int iKeyCode)
{
	switch (iKeyCode)
	{
	// Inverse of KeyDown to cancel out velocity when key is released
	case SDLK_LEFT:	m_pRacket->Right(); break;
	case SDLK_RIGHT: m_pRacket->Left(); break;
	default: break;
	}
}


/*
Draw the changes to the screen.
Remove the changing objects, redraw the strings and draw the changing objects again.
*/
void Breakout::DrawChanges()
{
	// Remove objects from their old positions
	UndrawChangingObjects();
	// Draw the text for the user
	DrawStrings();
	// Draw objects at their new positions
	DrawChangingObjects();
}
