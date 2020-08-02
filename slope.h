#pragma once

#include "global.h"
#include <algorithm>
#include "rectangle.h"

class Slope {
public:
	Slope() {};
	Slope(Vector2 p1, Vector2 p2):
		p1(p1), p2(p2)
	{
		if (this->p2.x - this->p1.x != 0) {
			this->slope = (fabs(this->p2.y) - fabs(this->p1.y)) / (fabs(this->p2.x) - fabs(this->p1.x));
		}
	}

	const inline float getSlope() const {
		return this->slope;
	}

	const bool collidesWith(const Rectangle& other) const {
		return
			(other.getRight() >= this->p2.x &&
				other.getLeft() <= this->p1.x &&
				other.getTop() <= this->p2.y &&
				other.getBottom() >= this->p1.y) ||
			(other.getRight() >= this->p1.x &&
				other.getLeft() <= this->p2.x &&
				other.getTop() <= this->p1.y &&
				other.getBottom() >= this->p2.y) ||
			(other.getLeft() <= this->p1.x &&
				other.getRight() >= this->p2.x &&
				other.getTop() <= this->p1.y &&
				other.getBottom() >= this->p2.y) ||
			(other.getLeft() <= this->p2.x &&
				other.getRight() >= this->p1.x &&
				other.getTop() <= this->p2.y &&
				other.getBottom() >= this->p1.y);
	}
	const inline Vector2 getP1() const { return this->p1; }
	const inline Vector2 getP2() const { return this->p2; }
private:
	Vector2 p1, p2;
	float slope;
};

