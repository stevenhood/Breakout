#include "header.h"
#include "templates.h"
#include "Breakout.h"

#define BASE_SCREEN_WIDTH 710
#define BASE_SCREEN_HEIGHT 600

int main(int argc, char *argv[])
{
	int iResult;
	Breakout oMain;

	char buf[1024];
	sprintf( buf, "Breakout", BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT );
	iResult = oMain.Initialise( buf, BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT, "Cornerstone Regular.ttf", 24 );
	iResult = oMain.MainLoop();
	oMain.Deinitialise();

	return iResult;
}
