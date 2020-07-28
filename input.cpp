#include "input.h"
/* keep track of keyboard state */

/*
* this functions get called at the beginning of each new frame
* to reset the keys that are no longer relevant
*/
void Input::beginNewFrame() {
	this->pressedKeys.clear();
	this->releasedKeys.clear();
}

/*
* this get called when a key has been pressed
*/
void Input::keyDownEvent(const SDL_Event& event) {
	this->pressedKeys[event.key.keysym.scancode] = true;
	this->heldKeys[event.key.keysym.scancode] = true;
}


/* 
* this get called when key is released
*/
void Input::keyUpEvent(const SDL_Event& event) {
	this->releasedKeys[event.key.keysym.scancode] = true;
	this->heldKeys[event.key.keysym.scancode] = false;
}

/*
* check if a certain key was pressed during the current frame
*/
bool Input::wasKeyPressed(SDL_Scancode key) {
	return this->pressedKeys[key];
}

/*
*check if a certain key was released during the current frame
*/
bool Input::wasKeyReleased(SDL_Scancode key) {
	return this->releasedKeys[key];
}

/*
* check if a certain key is currently being held
*/
bool Input::isKeyHeld(SDL_Scancode key) {
	return this->heldKeys[key];
}
