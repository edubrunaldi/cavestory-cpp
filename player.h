#pragma once

#include "global.h"
#include "animatedSprite.h"


class Graphics;

class Player: public AnimatedSprite {
public:
	Player();
	Player(Graphics& graphics, float x, float y);
	void draw(Graphics& graphics);
	void update(float elapsedTime);

	void moveLeft();
	void moveRight();
	void stopMoving();

	void animationDone(std::string currentAnimation);
	void setupAnimations();

private:
	float dx, dy;

	Direction facing;
};

