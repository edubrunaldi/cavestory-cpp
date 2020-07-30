#pragma once
#include <SDL.h>
#include <string>

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
protected:
	SDL_Rect sourceRect;
	SDL_Texture* spriteSheet;

private:
	float x, y;
};

