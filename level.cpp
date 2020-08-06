#include "level.h"
#include "graphics.h"
#include "utils.h"

#include "tinyxml2.h"

#include <SDL.h>

#include <sstream>
#include <algorithm>
#include <cmath>
#include "bat.h"

using namespace tinyxml2;

Level::Level() {}

Level::Level(std::string mapName, Graphics& graphics) :
	mapName(mapName),
	size(Vector2(0, 0))
{
	this->loadMap(mapName, graphics);
}

Level::~Level() {

}

void Level::loadMap(std::string mapName, Graphics& graphics) {
	//Parse the .tmx file
	XMLDocument doc;
	std::stringstream ss;
	ss << "content/maps/" << mapName << ".tmx"; //Pass in Map 1, we get maps/Map 1.tmx
	doc.LoadFile(ss.str().c_str());

	XMLElement* mapNode = doc.FirstChildElement("map");

	//Get the width and the height of the whole map and store it in _size
	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	this->size = Vector2(width, height);

	//Get the width and the height of the tiles and store it in _tileSize
	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	this->tileSize = Vector2(tileWidth, tileHeight);

	//Loading the tilesets
	XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset != NULL) {
		while (pTileset) {
			int firstgid;
			const char* source = pTileset->FirstChildElement("image")->Attribute("source");
			char* path;
			std::stringstream ss;
			ss <<  source;
			pTileset->QueryIntAttribute("firstgid", &firstgid);
			SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
			this->tilesets.push_back(Tileset(tex, firstgid));

			//Get all of the animations for that tileset
			XMLElement* pTileA = pTileset->FirstChildElement("tile");
			while (pTileA) {
				AnimatedTileInfo ati;
				ati.StartTileId = pTileA->IntAttribute("id") + firstgid;
				ati.TilesetsFirstGid = firstgid;
				XMLElement* pAnimation = pTileA->FirstChildElement("animation");
				while (pAnimation) {
					XMLElement* pFrame = pAnimation->FirstChildElement("frame");
					while (pFrame) {
						ati.TilesIds.push_back(pFrame->IntAttribute("tileid") + firstgid);
						ati.Duration = pFrame->IntAttribute("duration");
						pFrame = pFrame->NextSiblingElement("frame");
					}
					pAnimation = pAnimation->NextSiblingElement("animation");
				}
				this->animatedTileInfos.push_back(ati);
				pTileA = pTileA->NextSiblingElement("tile");
			}

			pTileset = pTileset->NextSiblingElement("tileset");
		}
	}

	//Loading the layers
	XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer != NULL) {
		while (pLayer) {
			//Loading the data element
			XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData != NULL) {
				while (pData) {
					//Loading the tile element
					XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != NULL) {
						int tileCounter = 0;
						while (pTile) {
							//Build each individual tile here
							//If gid is 0, no tile should be drawn. Continue loop
							if (pTile->IntAttribute("gid") == 0) {
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							//Get the tileset for this specific gid
							int gid = pTile->IntAttribute("gid");
							Tileset tls;
							int closest = 0;
							for (int i = 0; i < this->tilesets.size(); i++) {
								if (this->tilesets[i].FirstGid <= gid) {
									if (this->tilesets[i].FirstGid > closest) {
										closest = this->tilesets[i].FirstGid;
										tls = this->tilesets.at(i);
									}
								}
							}

							if (tls.FirstGid == -1) {
								//No tileset was found for this gid
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							//Get the position of the tile in the level
							int xx = 0;
							int yy = 0;
							xx = tileCounter % width;
							xx *= tileWidth;
							yy += tileHeight * (tileCounter / width);
							Vector2 finalTilePosition = Vector2(xx, yy);

							//Calculate the position of the tile in the tileset
							Vector2 finalTilesetPosition = this->getTilesetPosition(tls, gid, tileWidth, tileHeight);

							//Build the actual tile and add it to the level's tile list
							bool isAnimatedTile = false;
							AnimatedTileInfo ati;
							for (const AnimatedTileInfo animatedti: this->animatedTileInfos) {
								if (animatedti.StartTileId == gid) {
									ati = animatedti;
									isAnimatedTile = true;
									break;
								}
							}
							if (isAnimatedTile) {
								std::vector<Vector2> tilesetPositions;
								for (const int id : ati.TilesIds) {
									tilesetPositions.push_back(this->getTilesetPosition(tls, id, tileWidth, tileHeight));
								}
								AnimatedTile tile(tilesetPositions, ati.Duration, tls.Texture, Vector2(tileWidth, tileHeight), finalTilePosition);
								this->animatedTileList.push_back(tile);
							}
							else {
								Tile tile(tls.Texture, Vector2(tileWidth, tileHeight),
									finalTilesetPosition, finalTilePosition);
								this->tileList.push_back(tile);
							}
							tileCounter++;

							pTile = pTile->NextSiblingElement("tile");
						}
					}

					pData = pData->NextSiblingElement("data");
				}
			}

			pLayer = pLayer->NextSiblingElement("layer");
		}
	}

	// parse out the collisions
	XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
	if (pObjectGroup != NULL) {
		while (pObjectGroup) {
			const char* name = pObjectGroup->Attribute("name");
			std::stringstream ss;
			ss << name;
			if (ss.str() == "collisions") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						float x, y, width, height;
						x = pObject->FloatAttribute("x");
						y = pObject->FloatAttribute("y");
						width = pObject->FloatAttribute("width");
						height = pObject->FloatAttribute("height");
						this->collisionRects.push_back(Rectangle(
							std::ceil(x) * globals::SPRITE_SCALE,
							std::ceil(y) * globals::SPRITE_SCALE,
							std::ceil(width) * globals::SPRITE_SCALE,
							std::ceil(height) * globals::SPRITE_SCALE
						));

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			//Other objectgroups go here with an else if (ss.str() == "whatever")
			else if (ss.str() == "slopes") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						std::vector<Vector2> points;
						Vector2 p1;
						p1 = Vector2(std::ceil(pObject->FloatAttribute("x")), std::ceil(pObject->FloatAttribute("y")));

						XMLElement* pPolyline = pObject->FirstChildElement("polyline");
						if (pPolyline != NULL) {
							std::vector<std::string> pairs;
							const char* pointString = pPolyline->Attribute("points");

							std::stringstream ss;
							ss << pointString;
							Utils::split(ss.str(), pairs, ' ');
							//Now we have each of the pairs. Loop through the list of pairs
							//and split them into Vector2s and then store them in our points vector
							for (int i = 0; i < pairs.size(); i++) {
								std::vector<std::string> ps;
								Utils::split(pairs.at(i), ps, ',');
								points.push_back(Vector2(std::stoi(ps.at(0)), std::stoi(ps.at(1))));
							}
						}

						for (int i = 0; i < points.size(); i += 2) {
							this->slopes.push_back(Slope(
								Vector2((p1.x + points.at(i < 2 ? i : i - 1).x) * globals::SPRITE_SCALE,
									(p1.y + points.at(i < 2 ? i : i - 1).y) * globals::SPRITE_SCALE),
								Vector2((p1.x + points.at(i < 2 ? i + 1 : i).x) * globals::SPRITE_SCALE,
									(p1.y + points.at(i < 2 ? i + 1 : i).y) * globals::SPRITE_SCALE)
							));
						}

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			else if (ss.str() == "spawn points") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						float x = pObject->FloatAttribute("x");
						float y = pObject->FloatAttribute("y");
						const char* name = pObject->Attribute("name");
						std::stringstream ss;
						ss << name;
						if (ss.str() == "player") {
							this->spawnPoint = Vector2(std::ceil(x) * globals::SPRITE_SCALE,
								std::ceil(y) * globals::SPRITE_SCALE);
						}

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			else if (ss.str() == "doors") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				while (pObject) {
					float x = pObject->FloatAttribute("x");
					float y = pObject->FloatAttribute("y");
					float w = pObject->FloatAttribute("width");
					float h = pObject->FloatAttribute("height");
					Rectangle rect = Rectangle(x, y, w, h);

					XMLElement* pProperties = pObject->FirstChildElement("properties");
					while (pProperties) {
						XMLElement* pProperty = pProperties->FirstChildElement("property");
						while (pProperty) {
							const char* name = pProperty->Attribute("name");
							std::stringstream ss;
							ss << name;
							if (ss.str() == "destination") {
								const char* value = pProperty->Attribute("value");
								std::stringstream ss2;
								ss2 << value;
								Door door = Door(rect, ss2.str());
								this->doorList.push_back(door);
							}

							pProperty = pProperty->NextSiblingElement("property");
						}

						pProperties = pProperties->NextSiblingElement("properties");
					}


					pObject = pObject->NextSiblingElement("object");
				}
			}
			else if (ss.str() == "enemies") {
			float x, y;
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				while (pObject) {
					x = pObject->FloatAttribute("x");
					y = pObject->FloatAttribute("y");
					const char* name = pObject->Attribute("name");
					std::stringstream ss;
					ss << name;
					if (ss.str() == "bat") {
						this->enemies.push_back(new Bat(graphics, Vector2(std::floor(x)* globals::SPRITE_SCALE,
							std::floor(y)* globals::SPRITE_SCALE)));
					}


					pObject = pObject->NextSiblingElement("object");
				}
			
			}

			pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
		}
	}

}

Vector2 Level::getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight)
{
	int tilesetWidth, tilesetHeight;
	SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
	int tsxx = gid % (tilesetWidth / tileWidth) - 1;
	tsxx *= tileWidth;
	int tsyy = 0;
	int amt = ((gid - tls.FirstGid) / (tilesetWidth / tileWidth));
	tsyy = tileHeight * amt;
	Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);
	return finalTilesetPosition;
}

void Level::update(int elapsedTime, Player& player) {
	for (AnimatedTile& at : this->animatedTileList) {
		at.update(elapsedTime);
	}

	for (int i = 0; i < this->enemies.size(); ++i) {
		this->enemies.at(i)->update(elapsedTime, player);
	}
}

void Level::draw(Graphics& graphics) {
	for (int i = 0; i < this->tileList.size(); i++) {
		this->tileList.at(i).draw(graphics);
	}

	for (AnimatedTile& at : this->animatedTileList) {
		at.draw(graphics);
	}

	for (int i = 0; i < this->enemies.size(); i++) {
		this->enemies.at(i)->draw(graphics);
	}
}

std::vector<Rectangle> Level::checkTileCollisions(const Rectangle& other) {
	std::vector<Rectangle> others;
	for (int i = 0; i < this->collisionRects.size(); i++) {
		if (this->collisionRects.at(i).collidesWith(other)) {
			others.push_back(this->collisionRects.at(i));
		}
	}
	return others;
}

std::vector<Slope> Level::checkSlopeCollisions(const Rectangle& other)
{
	std::vector<Slope> others;
	for (const Slope slope : this->slopes) {
		if (slope.collidesWith(other)) {
			others.push_back(slope);
		}
	}
	return others;
}

std::vector<Door> Level::checkDoorCollisions(const Rectangle& other)
{
	std::vector<Door> others;
	for (const Door door : this->doorList) {
		if (door.collidesWith(other)) {
			others.push_back(door);
		}
	}
	return others;
}

std::vector<Enemy*> Level::checkEnemyCollisions(const Rectangle& other)
{
	std::vector<Enemy*> others;
	for (int i = 0; i < this->enemies.size(); i++) {
		if (this->enemies.at(i)->getBoundingBox().collidesWith(other)) {
			others.push_back(this->enemies.at(i));
		}
		else {
			this->enemies.at(i)->resetTouchedPlayer();
		}
	}
	return others;
}

const Vector2 Level::getPlayerSpawnPoint() const {
	return this->spawnPoint;
}
