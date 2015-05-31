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
	void DrawChanges();

private:
	static const int m_iMaxNumObjects, m_iNumRows, m_iNumCols;
	State m_State;
	Racket *m_pRacket;
	Ball *m_pBall;
	int m_iBricksStartIndex;

	int SetupBricks(int iIndex);
	void CheckBrickCollide(void);
};

