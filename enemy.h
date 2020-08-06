#pragma once

#include "animatedSprite.h"
class Player;


class Enemy: public AnimatedSprite {
public:
	Enemy();
	Enemy(Graphics& graphics, std::string filePath, int sourceX, int sourceY,
		int width, int height, Vector2 spawnPoint, int timeToUpdate);

	virtual void update(int elapsedTime, Player& player);
	virtual void draw(Graphics& graphics);
	virtual void touchPlayer(Player* player) = 0;

	const inline int getMaxHealth() const { return this->maxHealth; }
	const inline int getCurrentHealth() const { return this->currentHealth; }
	void resetTouchedPlayer();
protected:
	Direction direction;

	int maxHealth;
	int currentHealth;

	float startingX, startingY;
	bool shouldMoveUp;
	bool lasFrameTouched;
};