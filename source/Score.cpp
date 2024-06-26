#include "Score.h"

Score::Score()
{
	player1Score = 0;
	player2Score = 0;

	// Render text
	SDL_Color textColor = { GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE };
	if (!mP1TextTexture.loadFromRenderedText("0", textColor))
	{
		std::cout << "Failed to render text texture!\n";
	}
	if (!mP2TextTexture.loadFromRenderedText("0", textColor))
	{
		std::cout << "Failed to render text texture!\n";
	}
	mGameContinueTexture.loadFromRenderedText("Press 'R' to restart!", textColor);
	hasPlayerWon = false;
}

Score::~Score()
{
	mP1TextTexture.free();
	mP2TextTexture.free();
}

void Score::IncrementScore(bool forPlayer1)
{
	if (forPlayer1) ++player1Score;
	else ++player2Score;

	std::cout << player1Score << '\t' << player2Score << '\n';
}

void Score::HandlePlayerWin(GameManager& gameManager)
{
	SDL_Color textColor = { GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE };
	if (player1Score > 10)
	{
		mPlayerWinTexture.loadFromRenderedText("Player 1 win!", textColor);
		gameManager.GameEventPauseToggle();
		hasPlayerWon = true;
	}
	else if (player2Score > 10)
	{
		mPlayerWinTexture.loadFromRenderedText("Player 2 win!", textColor);
		gameManager.GameEventPauseToggle();
		hasPlayerWon = true;
	}
}

void Score::RenderPlayerWinText()
{
	mPlayerWinTexture.Render((SCREEN_WIDTH - mPlayerWinTexture.getWidth()) / 2, (SCREEN_HEIGHT - mPlayerWinTexture.getHeight()) / 2 - mPlayerWinTexture.getHeight());
	mGameContinueTexture.Render((SCREEN_WIDTH - mGameContinueTexture.getWidth()) / 2, (SCREEN_HEIGHT - mPlayerWinTexture.getHeight()) / 2);
}

bool Score::HasPlayerWon()
{
	return hasPlayerWon;
}

void Score::UpdateScoreText()
{
	std::stringstream p1ScoreTextStream;
	std::stringstream p2ScoreTextStream;
	p1ScoreTextStream << player1Score;
	p2ScoreTextStream << player2Score;
	std::string player1ScoreString;
	std::string player2ScoreString;
	p1ScoreTextStream >> player1ScoreString;
	p2ScoreTextStream >> player2ScoreString;
	SDL_Color textColor = { GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE };
	mP1TextTexture.loadFromRenderedText(player1ScoreString, textColor);
	mP2TextTexture.loadFromRenderedText(player2ScoreString, textColor);
}

void Score::RenderScore()
{
	int halfScreen{ SCREEN_WIDTH / 2 };
	mP1TextTexture.Render(halfScreen - mP1TextTexture.getWidth() - 50, 50);
	mP2TextTexture.Render(halfScreen + 50 , 50);
}

void Score::Reset()
{
	player1Score = 0;
	player2Score = 0;
	hasPlayerWon = false;
}