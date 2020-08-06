#pragma once

#include "sprite.h"
#include "player.h"
class Graphics;

class Hud {
public:
	Hud();
	Hud(Graphics& graphics, Player& player);
	void update(int elapsedTime, Player& player);
	void draw(Graphics& graphics);
private:
	Player player;

	// health sprite
	Sprite healthBarSprite;
	Sprite healthNumer1;
	Sprite currentHealthBar;

	// Exp sprites
	Sprite lvWord;
	Sprite lvNumber;
	Sprite expBar;

	// weapon info
	Sprite slash;
	Sprite dashes;
};

