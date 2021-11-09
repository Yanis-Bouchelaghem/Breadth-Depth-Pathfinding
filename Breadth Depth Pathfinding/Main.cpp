#include "Game.h"

int main(void)
{
	Game game{800,600,60,"Pathfinding robot"};

	while (!game.GameShouldClose())
	{
		game.Tick();
	}
	return 0;
}