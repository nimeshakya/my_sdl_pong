#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#include "Texture.h"

class GameManager
{
public:
	GameManager();
	// start game
	void Start();
	// returns the quit status
	bool IsGameQuitted();
	// quits the game
	void QuitGame();
	// pause the game
	void PauseToggleGame();
	// returns pause status;
	bool IsPaused();
	void GameEventPauseToggle();
	bool IsPausedByGameEvent();
	// checks if there is an event
	bool HasEvent();
	// returns the event object
	SDL_Event GetEvent();
	// set the pause text
	void SetPauseText(std::string info);
	// renders paused text
	void RenderPause();
	// reset all states
	void Reset();
private:
	bool quit;
	bool paused; // player pause
	bool gameEventPause; // pause due to game event
	SDL_Event e;
	Texture mPausedTextTexture;
};