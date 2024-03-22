#include "Score.h"

void Score::IncrementScore(bool forPlayer1)
{
	if (forPlayer1) ++player1Score;
	else ++player2Score;

	std::cout << player1Score << '\t' << player2Score << '\n';
}

void Score::Reset()
{
	player1Score = 0;
	player2Score = 0;
}