#pragma once

#include <map>
#include <string>
#include <SDL.h>

struct SDL_Window;
struct SDL_Renderer;

/* Hold all information dealing with graphics for the game*/

class Graphics {
public:
	Graphics();
	~Graphics();

	
	
	/* SDL_Surface* loadImage
	Loads an iamge to the sprintSheets map if it doesn't already exist.
	As a result, each image will only ever be loaded once
	Returns the image from the map regardless of whether or not it was just loadded
	*/
	SDL_Surface* loadImage(const std::string& filePath);

	/* void blitSurface
	Draw a texture to a certain part of the screen
	*/
	void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	/* void flip
	Renders everything to the screen
	*/
	void flip();
	/* void clear
	Clears the screen
	*/
	void clear();

	/*SDL_Renderer* getRenderer
	Returns the renderer
	*/
	SDL_Renderer* getRenderer() const;
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	std::map<std::string, SDL_Surface*> sprinteSheets;
};