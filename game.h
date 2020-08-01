#pragma once
#define SDL_MAIN_HANDLED

#include "player.h"
#include "level.h"
class Graphics;

class Game
{
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphics& graphics);
	void update(float elapsedTime);

	Player player;
	Level level;
};

