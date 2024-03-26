#include "GameManager.h"

GameManager::GameManager() : e{ NULL } // for some reason initialize event like this
{
	quit = false ;
	paused = true ;
	gameEventPause = true;
	SDL_Color textColor = { GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE };
	mPausedTextTexture.loadFromRenderedText("Paused!", textColor);
}

void GameManager::Start()
{
	paused = false;
	gameEventPause = false;
}

bool GameManager::IsGameQuitted()
{
	return quit;
}

void GameManager::QuitGame()
{
	quit = true;
}

void GameManager::PauseToggleGame()
{
	paused = !paused;
}

bool GameManager::IsPaused()
{
	return paused;
}

void GameManager::GameEventPauseToggle()
{
	gameEventPause = !gameEventPause;
}

bool GameManager::IsPausedByGameEvent()
{
	return gameEventPause;
}

bool GameManager::HasEvent()
{
	return SDL_PollEvent(&e) != 0;
}

SDL_Event GameManager::GetEvent()
{
	return e;
}
void GameManager::SetPauseText(std::string info)
{
	SDL_Color textColor = { GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE };
	mPausedTextTexture.loadFromRenderedText(info, textColor);
}
void GameManager::RenderPause()
{
	if (paused) SetPauseText("Paused!");
	if (paused && gameEventPause) SetPauseText("Press [space] to start"); // start of the game
	mPausedTextTexture.Render((SCREEN_WIDTH - mPausedTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - mPausedTextTexture.getHeight()) / 2);
}
void GameManager::Reset()
{
	gameEventPause = false;
	paused = false;
	SetPauseText("Pause!");
}