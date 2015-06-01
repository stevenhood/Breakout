#pragma once
#include "BaseEngine.h"
#include "Brick.h"
#include "Racket.h"
#include "Ball.h"

class Breakout :
	public BaseEngine
{
public:
	enum State {
		stateInit,
		stateMain,
		statePaused,
		stateEnd
	};

	Breakout(void);
	~Breakout(void);
	int InitialiseObjects();
	void SetupBackgroundBuffer();
	void GameAction();
	void KeyDown(int iKeyCode);
	void KeyUp(int iKeyCode);
	void MouseMoved(int iX, int iY);
	void MouseUp(int iButton, int iX, int iY);
	void DrawChanges();
	void DrawStrings(void);

private:
	static const int m_iMaxNumObjects, m_iNumRows, m_iNumCols, m_iMaxNumLives;
	State m_State;
	Racket *m_pRacket;
	Ball *m_pBall;
	int m_iBricksStartIndex;
	int m_iNumLives;
	int m_iScore;

	void Reset(void);
	int SetupBricks(int iIndex);
	void CheckBrickCollisions(void);
	void GameOver(void);
};

