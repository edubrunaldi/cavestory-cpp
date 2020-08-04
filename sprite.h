#pragma once
#include <SDL.h>
#include <string>
#include "rectangle.h"
#include "global.h"

class Graphics;
/* Sprite class
Hold all information for individual sprites
*/

class Sprite {
public:
	Sprite();
	Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int hieght, float posX, float posY);

	virtual ~Sprite();
	virtual void update();
	void draw(Graphics& graphics, int x, int y);

	const Rectangle getBoundingBox() const;
	const sides::Side getCollisionSide(Rectangle& other) const;

	const inline float getX() const { return this->x; }
	const inline float getY() const { return this->y; }

	void setSourceRectX(int value);
	void setSourceRectY(int value);
	void setSourceRectWidth(int value);
	void setSourceRectHeight(int value);

protected:
	SDL_Rect sourceRect;
	SDL_Texture* spriteSheet;
	float x, y;

	Rectangle boundingBox;
};


