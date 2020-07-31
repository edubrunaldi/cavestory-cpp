#pragma once

#include "sprite.h"
#include <map>
#include <string>
#include <vector>
#include "global.h"
class Graphics;

/*AnimatedSprite class
Hold logic for animating sprites
*/

class AnimatedSprite: public Sprite {
public:
	AnimatedSprite();
	AnimatedSprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY,
		int width, int height, float posX, float posY, float timeToUpdate);
	~AnimatedSprite();

	/* void playANimation
	PlayAnimation the animation provided if it's not already playing
	*/
	void playAnimation(std::string animation, bool once = false);


	/* void update
	Updates the aniamted sprinte (timer)
	*/
	void update(int elapsedTime);

	/* void draw
	Draws the sprite to the screen
	*/
	void draw(Graphics& graphics, int x, int y);

	

protected:
	double timeToUpdate;
	bool currentAnimationOnce;
	std::string currentAnimation;

	/* void addAnimation
	Adds an animation to the map of animations for the sprite
	*/
	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

	/* void resetAnimations
	Reset all animations associated with this sprite
	*/
	void resetAnimations();


	/* void stopAnimations
	Stops the current animation
	*/
	void stopAnimations();

	/* void setVisible
	Changes the visibility of the animated sprite
	*/
	void setVisible(bool visible);


	/* void animationDone
	Logic that happens when an animation ends
	*/
	virtual void animationDone(std::string currentAnimation) = 0;

	/* void setupAnimations
	A required function that sets up all animations for a sprite
	*/
	virtual void setupAnimations() = 0;

private:
	std::map<std::string, std::vector<SDL_Rect> > animations;
	std::map<std::string, Vector2> offsets;

	int frameIndex;
	double timeElapsed;
	bool visible;
};

