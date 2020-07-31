#include "player.h"
#include "graphics.h"

namespace player_constants {
	const float WALK_SPEED = 0.2f;
}

Player::Player() {
}

Player::Player(Graphics& graphics, float x, float y):
	AnimatedSprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, x, y, 100)
{
	graphics.loadImage("content/sprites/MyChar.png");
	this->setupAnimations();
	this->playAnimation("RunRight");
	this->facing = RIGHT;
}

void Player::draw(Graphics& graphics) {
	AnimatedSprite::draw(graphics, this->x, this->y);
}

void Player::update(float elapsedTime) {
	this->x += this->dx * elapsedTime;
	AnimatedSprite::update(elapsedTime);
}

void Player::moveLeft() {
	this->dx = -player_constants::WALK_SPEED;
	this->playAnimation("RunLeft");
	this->facing = LEFT;
}

void Player::moveRight() {
	this->dx = player_constants::WALK_SPEED;
	this->playAnimation("RunRight");
	this->facing = RIGHT;
}

void Player::stopMoving() {
	this->dx = 0.0f;
	this->playAnimation(this->facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::animationDone(std::string currentAnimation) {
	
}

void Player::setupAnimations() {
	this->addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
}
