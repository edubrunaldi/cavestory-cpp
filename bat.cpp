#include "bat.h"
#include "player.h"

Bat::Bat() {
}

Bat::Bat(Graphics& graphics, Vector2 spawnPoint) :
	Enemy(graphics, "content/sprites/NpcCemet.png", 32, 32, 16, 16, spawnPoint, 140)
{
	this->setupAnimations();
	this->playAnimation("FlyLeft");
}

void Bat::update(int elapsedTime, Player& player) {
	this->direction = player.getX() > this->x ? RIGHT : LEFT;
	this->playAnimation(this->direction == RIGHT ? "FlyRight" : "FlyLeft");

	//move up or down
	this->y += this->shouldMoveUp ? -.01 : .01;
	if (this->y > (this->startingY + 20) || this->y < this->startingY - 20) {
		this->shouldMoveUp = !this->shouldMoveUp;
	}

	Enemy::update(elapsedTime, player);
}

void Bat::draw(Graphics& graphics) {
	Enemy::draw(graphics);
}

void Bat::touchPlayer(Player* player) {
	if (!this->lasFrameTouched) {
		player->gainHealth(-1);
		this->lasFrameTouched = true;
	}
}

void Bat::animationDone(std::string currentAnimation) {
}

void Bat::setupAnimations() {
	this->addAnimation(3, 2, 32, "FlyLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 2, 48, "FlyRight", 16, 16, Vector2(0, 0));
}
