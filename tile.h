#pragma once

#include "global.h"

struct SDL_Texture;
class Graphics;

class Tile {
public:
	Tile();
	Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 positon);
	void update(int elapsedTime);
	void draw(Graphics& graphics);
private:
	SDL_Texture* tileset;
	Vector2 size;
	Vector2 tilesetPosition;
	Vector2 position;
};

