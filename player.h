#pragma once

#include "global.h"
#include "animatedSprite.h"
#include "slope.h"
#include "enemy.h"

class Door;
class Level;
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
	const inline int getMaxHealth() const { return this->maxHealth; }
	const inline int getCurrentHealth() const { return this->currentHealth; }

	void handleTileCollisions(std::vector<Rectangle>& others);
	void handleSlopeCollisions(std::vector<Slope>& others);
	void handleDoorCollision(std::vector<Door>& others, Level& level, Graphics& graphics);
	void handleEnemyCollisions(std::vector<Enemy*>& others);
	
	void gainHealth(int amount);

private:
	float dx, dy;

	Direction facing;

	bool grounded;

	bool lookingUp;
	bool lookingDown;

	int maxHealth;
	int currentHealth;
};

