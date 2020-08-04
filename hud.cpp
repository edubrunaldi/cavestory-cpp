#include "hud.h"
#include "graphics.h"
#include <cmath>

Hud::Hud() {
}

Hud::Hud(Graphics& graphics, Player& player) {
	this->player = player;
	this->healthBarSprite = Sprite(graphics, "content/sprites/TextBox.png", 0, 40, 64, 8, 35, 70);
	this->healthNumer1 = Sprite(graphics, "content/sprites/TextBox.png", 0, 56, 8, 8, 66, 70);
	this->currentHealthBar= Sprite(graphics, "content/sprites/TextBox.png", 0, 25, 39, 5, 83, 72);

	this->lvWord = Sprite(graphics, "content/sprites/TextBox.png", 81, 81, 11, 7, 38, 55);
	this->lvNumber = Sprite(graphics, "content/sprites/TextBox.png", 0, 56, 8, 8, 66, 52 );
	this->expBar = Sprite(graphics, "content/sprites/TextBox.png", 0, 72, 40, 8, 83, 52);

	this->slash = Sprite(graphics, "content/sprites/TextBox.png", 72, 48, 8, 8,100, 36);
	this->dashes = Sprite(graphics, "content/sprites/TextBox.png", 81, 51, 15, 11, 132, 26);
}

void Hud::update(int elapsedTime) {
	this->healthNumer1.setSourceRectX(8 * this->player.getCurrentHealth());
	
	//calculate the width of the health bar
	// 100% = 39px
	float num = (float)this->player.getCurrentHealth() / this->player.getMaxHealth();
	this->currentHealthBar.setSourceRectWidth(std::floor(num * 39));
}

void Hud::draw(Graphics& graphics) {
	this->healthBarSprite.draw(graphics, this->healthBarSprite.getX(), this->healthBarSprite.getY());
	this->healthNumer1.draw(graphics, this->healthNumer1.getX(), this->healthNumer1.getY());
	this->currentHealthBar.draw(graphics, this->currentHealthBar.getX(), this->currentHealthBar.getY());
	
	this->lvWord.draw(graphics, this->lvWord.getX(), this->lvWord.getY());
	this->lvNumber.draw(graphics, this->lvNumber.getX(), this->lvNumber.getY());
	this->expBar.draw(graphics, this->expBar.getX(), this->expBar.getY());

	this->slash.draw(graphics, this->slash.getX(), this->slash.getY());
	this->dashes.draw(graphics, this->dashes.getX(), this->dashes.getY());
}
