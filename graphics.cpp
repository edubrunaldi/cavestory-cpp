#include <SDL.h>
#include "graphics.h"

/* Hold all information dealing with graphics for the game*/

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(640, 480, 0, &this->window, &this->renderer);
	SDL_SetWindowTitle(this->window, "Cavestory");
}


Graphics::~Graphics() {
	SDL_DestroyWindow(this->window);
}