#pragma once

#include "tile.h"
#include <vector>

class AnimatedTile: public Tile {
public:
	AnimatedTile(std::vector<Vector2> tilesetPositions, int duration, SDL_Texture* tileset, Vector2 size, Vector2 position);
	void update(int elapsedTime);
	void draw(Graphics& graphics);
protected:
	int amountOfTime = 0;
	bool notDone = false;
private:
	std::vector<Vector2> tilesetPositions;
	int tileToDraw;
	int duration;
};

struct AnimatedTileInfo {
public:
	int TilesetsFirstGid;
	int StartTileId;
	std::vector<int> TilesIds;
	int Duration;
};