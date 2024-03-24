#pragma once

#include <iostream>
#include <SDL.h>
#include <string>
#include <sstream>

#include "GameWindow.h"
#include "Texture.h"

class Score
{
public: 
	Score();
	~Score();
	// increases player's score
	void IncrementScore (bool forPlayer1);
	void UpdateScoreText();
	void RenderScore();
	void Reset();
private:
	int player1Score;
	int player2Score;
	Texture mP1TextTexture;
	Texture mP2TextTexture;
};