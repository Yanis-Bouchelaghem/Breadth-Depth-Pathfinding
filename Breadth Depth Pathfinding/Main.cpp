#include "Game.h"
#include "Settings.h"
int main(void)
{
	Game game(settings::screenWidth,
			  settings::screenHeight,
			  settings::boardScreenPos,
			  settings::fps,
			  settings::title);

	while (!game.GameShouldClose())
	{
		game.Tick();
	}
	return 0;
}