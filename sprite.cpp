#include "sprite.h"
#include "graphics.h"
#include "global.h"

Sprite::Sprite() {}

Sprite::Sprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int hieght,
	float posX, float posY):
	x(posX),
	y(posY)
{
	this->sourceRect.x = sourceX;
	this->sourceRect.y = sourceY;
	this->sourceRect.w = width;
	this->sourceRect.h = hieght;

	this->spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	if (this->spriteSheet == NULL) {
		printf("\nError: Unable to load image\n");
	}
}

Sprite::~Sprite()
{
}

void Sprite::update()
{
}

void Sprite::draw(Graphics& graphics, int x, int y) {
	SDL_Rect destinationRectangle = { x, y, this->sourceRect.w * globals::SPRITE_SCALE ,
		this->sourceRect.h * globals::SPRITE_SCALE };
	graphics.blitSurface(this->spriteSheet, &this->sourceRect, &destinationRectangle);
}
