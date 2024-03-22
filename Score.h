#pragma once

#include <iostream>
#include <SDL.h>
#include "GameWindow.h"

class Score
{
public: 
	Score() : player1Score{ 0 }, player2Score{ 0 } {}

	// increases player's score
	void IncrementScore (bool forPlayer1);
	void Reset();
private:
	int player1Score;
	int player2Score;
};