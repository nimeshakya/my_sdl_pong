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
#include "Texture.h"
#include "GameAudio.h"

// initialize SDL and subsystems
bool init();
// load medias and textures
bool loadmedia();
// shut down SDL and subsystems
void close();

SDL_Window* gWindow{ NULL };
SDL_Renderer* gRenderer{ NULL };
TTF_Font* gFont{ NULL };

Mix_Chunk* gAudioBeep{ NULL };
Mix_Chunk* gAudioPeep{ NULL };
Mix_Chunk* gAudioPlop{ NULL };

bool init()
{
	bool success{ true }; // flag

	// initializing subsystem
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

	// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "SDL_image could not initialize! SDL_image ERROR: " << IMG_GetError() << '\n';
		return !success;
	}

	// Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf could not initialize! SDL_ttf ERROR: " << TTF_GetError() << '\n';
		return !success;
	}

	// Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer ERROR: " << Mix_GetError() << '\n';
		return !success;
	}

	return success;
}

bool loadmedia()
{
	bool success{ true }; // success flag

	// load all medias (img, ttf) here
	gFont = TTF_OpenFont("assets/VCR_OSD_MONO_1.001.ttf", 50);
	if (gFont == NULL)
	{
		std::cout << "Failed to load font! SDL_ttf ERROR: " << TTF_GetError() << '\n';
		return !success;
	}

	// load sound effects
	gAudioBeep = Mix_LoadWAV("assets/beep.wav");
	if (gAudioBeep == NULL)
	{
		std::cout << "Failed to load beep sound effect! SDL_mixer ERROR: " << Mix_GetError() << '\n';
		return !success;
	}
	gAudioPeep = Mix_LoadWAV("assets/peep.wav");
	if (gAudioPeep == NULL)
	{
		std::cout << "Failed to load peep sound effect! SDL_mixer ERROR: " << Mix_GetError() << '\n';
		return !success;
	}
	gAudioPlop = Mix_LoadWAV("assets/plop.wav");
	if (gAudioPlop == NULL)
	{
		std::cout << "Failed to load plop sound effect! SDL_mixer ERROR: " << Mix_GetError() << '\n';
		return !success;
	}

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
				score.UpdateScoreText();

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

				score.RenderScore();

				// present rendered objects
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	close();
	return 0;
}