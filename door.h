#pragma once

#include "rectangle.h"
#include "global.h"
#include <string>

class Door: public Rectangle {
public:
	Door() {}
	Door(Rectangle r, std::string destination):
		Rectangle(r.getLeft() * globals::SPRITE_SCALE, r.getTop() * globals::SPRITE_SCALE,
			r.getWidth() * globals::SPRITE_SCALE, r.getHeight() * globals::SPRITE_SCALE),
		destination(destination) {}

	const inline Rectangle getRectangle() const { return this->getRect(); }
	const inline std::string getDestination() const { return this->destination; }

private:
	std::string destination;
};

