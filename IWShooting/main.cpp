#include "Common.h"

INT WINAPI WinMain(HINSTANCE hinst, HINSTANCE, LPSTR, INT)
{	
	CGame *game = new CGame();
	game->run();

	return 0;
}
