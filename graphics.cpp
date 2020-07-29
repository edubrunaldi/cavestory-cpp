#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "global.h"
/* Hold all information dealing with graphics for the game*/

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &this->window, &this->renderer);
	SDL_SetWindowTitle(this->window, "Cavestory");
}


Graphics::~Graphics() {
	SDL_DestroyWindow(this->window);
}

SDL_Surface* Graphics::loadImage(const std::string& filePath) {
	if (this->sprinteSheets.count(filePath) == 0) {
		this->sprinteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return this->sprinteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle) {
	SDL_RenderCopy(this->renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip() {
	SDL_RenderPresent(this->renderer);
}

void Graphics::clear() {
	SDL_RenderClear(this->renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
	return this->renderer;
}
