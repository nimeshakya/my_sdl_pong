// C++ libraries
#include <iostream>
// SDL and extensions
#include <SDL.h>
// Custom headers
#include "GameWindow.h"
#include "Border.h"
#include "Paddle.h"
#include "BallSpawnner.h"
#include "Ball.h"
#include "Score.h"

// initialize SDL and subsystems
bool init();
// load medias and textures
bool loadmedia();
// shut down SDL and subsystems
void close();

SDL_Window* gWindow{ NULL };
SDL_Renderer* gRenderer{ NULL };

bool init()
{
	bool success{ true }; // flag

	// initializing subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_ERROR: " << SDL_GetError() << '\n';
		return !success;
	}

	// creating window and handling error
	gWindow = SDL_CreateWindow("my pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		std::cout << "Window could not be created! SDL_ERROR: " << SDL_GetError() << '\n';
		return !success;
	}

	// creating renderer and handling error
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL)
	{
		std::cout << "Renderer could not be created! SDL_ERROR: " << SDL_GetError() << '\n';
		return !success;
	}

	return success;
}

bool loadmedia()
{
	bool success{ true }; // success flag

	// load all medias (img, ttf) here

	return success;
}

void close()
{
	// destroy window
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gRenderer = NULL;

	// quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if (!init())
	{
		std::cout << "Failed to initialize SDL!\n";
	}
	else
	{
		if (!loadmedia())
		{
			std::cout << "Failed to load media!\n";
		}
		else
		{
			// game loop flag
			bool quit{ false };
			SDL_Event e;

			// Game Objects
			// border
			Border borderTop{ 0,0 };
			Border borderBot{ 0, SCREEN_HEIGHT - UNIT_LEN };

			// paddle
			Paddle paddleLeft{ UNIT_LEN, (SCREEN_HEIGHT - UNIT_LEN * 5) / 2 };
			Paddle paddleRight{ SCREEN_WIDTH - UNIT_LEN * 2, (SCREEN_HEIGHT - UNIT_LEN * 5) / 2 };

			// ball spawnner
			BallSpawnner ballSpawnner;

			// ball
			Ball ball{ ballSpawnner.GetSpawnPosition() };

			// for time calculations
			Uint32 lastUpdate{ SDL_GetTicks() };
			double deltaTime{ 0.0 };

			// tracking scores
			Score score;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				paddleLeft.HandleMovement(true);
				paddleRight.HandleMovement(false);

				// time update start (record)
				Uint32 currentTick{ SDL_GetTicks() };
				deltaTime = (currentTick - lastUpdate) / 1000.0f;
				if (deltaTime > 0.5)
				{
					deltaTime = 0.5;
				}

				// update codes here
				paddleLeft.Update(deltaTime);
				paddleRight.Update(deltaTime);

				ball.HandleCollision(paddleLeft, paddleRight, borderTop, borderBot);
				ball.Update(deltaTime);

				// ball goes beyond screen
				ball.HandleOutOfBound(ballSpawnner.GetSpawnPosition(), score);

				// time update end (reset)
				lastUpdate = currentTick;

				// clear renderer
				SDL_SetRenderDrawColor(gRenderer, GameObjColor::BG_RED, GameObjColor::BG_GREEN, GameObjColor::BG_BLUE, 0xFF);
				SDL_RenderClear(gRenderer);
				
				// render objects
				borderTop.Render();
				borderBot.Render();
				paddleLeft.Render();
				paddleRight.Render();
				ballSpawnner.Render();
				ball.Render();

				// present rendered objects
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	close();
	return 0;
}