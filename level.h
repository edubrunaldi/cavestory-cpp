#pragma once

#include "global.h"
#include "rectangle.h"
#include "slope.h"
#include "animatedTile.h"
#include <vector>
#include <string>
#include "tile.h"
#include "door.h"

class Player;
class Graphics;
class Enemy;
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;

class Level {
public: 
	Level();
	Level(std::string mapName, Graphics& graphics);
	~Level();

	void update(int elapsedTime, Player& player);
	void draw(Graphics& graphics);

	std::vector<Rectangle> checkTileCollisions(const Rectangle& other);
	std::vector<Slope> checkSlopeCollisions(const Rectangle& other);
	std::vector<Door> checkDoorCollisions(const Rectangle & other);
	std::vector<Enemy*> checkEnemyCollisions(const Rectangle& other);
	const Vector2 getPlayerSpawnPoint() const;
private:
	std::string mapName;
	Vector2 spawnPoint;
	
	Vector2 size;
	Vector2 tileSize;

	SDL_Texture* backgroundTexture;

	std::vector<Tile> tileList;
	std::vector<Tileset> tilesets;
	std::vector<Rectangle> collisionRects;
	std::vector<Slope> slopes;
	std::vector<AnimatedTile> animatedTileList;
	std::vector<AnimatedTileInfo> animatedTileInfos;
	std::vector<Door> doorList;
	std::vector<Enemy*> enemies;

	void loadMap(std::string mapName, Graphics& graphics);
	Vector2 getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight);
};

// tileset structure

struct Tileset {
	SDL_Texture* Texture;
	int FirstGid;

	Tileset() {
		this->FirstGid = -1;
	}

	Tileset(SDL_Texture* texture, int firstGid) {
		this->Texture = texture;
		this->FirstGid = firstGid;
	}
};

