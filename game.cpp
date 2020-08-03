#include <SDL.h>
#include <algorithm>

#include "game.h"
#include "graphics.h"
#include "input.h"
/* This class hold all information for our main game loop */

namespace {
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game()
{
}

void Game::gameLoop() {
	Graphics graphics;
	Input input;
	SDL_Event event;

	
	this->level = Level("Map 1", Vector2(100, 100), graphics);
	this->player = Player(graphics, this->level.getPlayerSpawnPoint());

	int LAST_UPDATE_TIME = SDL_GetTicks();
	// Start the game loop
	while (true) {
		input.beginNewFrame();

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		}

		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
			return;
		}
		else if (input.isKeyHeld(SDL_SCANCODE_LEFT)) {
			this->player.moveLeft();
		}
		else if (input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
			this->player.moveRight();
		}

		if (input.isKeyHeld(SDL_SCANCODE_UP)) {
			this->player.lookUp();
		}
		else if (input.isKeyHeld(SDL_SCANCODE_DOWN)) {
			this->player.lookDown();
		}

		if (input.wasKeyPressed(SDL_SCANCODE_Z) == true) {
			this->player.jump();
		}

		if (input.wasKeyReleased(SDL_SCANCODE_UP)) {
			this->player.stopLookingUp();
		}
		if (input.wasKeyReleased(SDL_SCANCODE_DOWN)) {
			this->player.stopLookingDown();
		}

		if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
			this->player.stopMoving();
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics& graphics) {
	graphics.clear();

	this->level.draw(graphics);
	this->player.draw(graphics);

	graphics.flip();
}

void Game::update(float elapsedTime) {
	this->player.update(elapsedTime);
	this->level.update(elapsedTime);

	// check collisions
	std::vector<Rectangle> others;
	if ((others = this->level.checkTileCollisions(this->player.getBoundingBox())).size() > 0) {
		//Player collided with at least one tile. Handle it.
		this->player.handleTileCollisions(others);
	}

	std::vector<Slope> otherSlopes;
	if ((otherSlopes = this->level.checkSlopeCollisions(this->player.getBoundingBox())).size() > 0) {
		this->player.handleSlopeCollisions(otherSlopes);
	}
}
