#pragma once

#include "global.h"

class Rectangle {
public:
	Rectangle() {}

	Rectangle(int x, int y, int width, int height) :
		x(x),
		y(y),
		width(width),
		height(height)
	{}

	const int getCenterX() const { return this->x + this->width / 2; }
	const int getCenterY() const { return this->y + this->height / 2; }

	const int getLeft() const { return this->x; }
	const int getRight() const { return this->x + this->width; }
	const int getTop() const { return this->y; }
	const int getBottom() const { return this->y + this->height; }

	const int getWidth() const { return this->width; }
	const int getHeight() const { return this->height; }

	const int getSide(const sides::Side side) const {
		return
			side == sides::LEFT ? this->getLeft() :
			side == sides::RIGHT ? this->getRight() :
			side == sides::TOP ? this->getTop() :
			side == sides::BOTTOM ? this->getBottom() :
			sides::NONE;
	}

	//bool collidesWith
	//Takes in another Rectangle and checks if the two are colliding
	const bool collidesWith(const Rectangle& other) const {
		return
			this->getRight() >= other.getLeft() &&
			this->getLeft() <= other.getRight() &&
			this->getTop() <= other.getBottom() &&
			this->getBottom() >= other.getTop();
	}

	const bool isValidRectangle() const {
		return (this->x >= 0 && this->y >= 0 && this->width >= 0 && this->height >= 0);
	}

private:
	int x, y, width, height;
};