#pragma once

#include "global.h"
#include "animatedSprite.h"
#include "slope.h"


class Graphics;

class Player: public AnimatedSprite {
public:
	Player();
	Player(Graphics& graphics, Vector2 spawnPoint);
	void draw(Graphics& graphics);
	void update(float elapsedTime);

	void moveLeft();
	void moveRight();
	void stopMoving();

	void lookUp();
	void stopLookingUp();
	void lookDown();
	void stopLookingDown();

	void jump();

	void animationDone(std::string currentAnimation);
	void setupAnimations();

	const float getX() const;
	const float getY() const;

	void handleTileCollisions(std::vector<Rectangle>& others);
	void handleSlopeCollisions(std::vector<Slope>& others);

private:
	float dx, dy;

	Direction facing;

	bool grounded;

	bool lookingUp;
	bool lookingDown;
};

