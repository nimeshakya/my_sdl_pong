#include "Ball.h"

#include <iostream>

void Ball::Update(double deltaTime)
{
	mPosition += Vector2(mVelX, mVelY) * BALL_SPEED * deltaTime;
}

void Ball::HandleCollision(const Paddle& paddle1, const Paddle& paddle2, const Border& borderTop, const Border& borderBot)
{
	CollideWithPaddle(HandlePaddleCollision(paddle1));
	CollideWithPaddle(HandlePaddleCollision(paddle2));
	CollideWithBorder(HandleBorderCollision(borderTop));
	CollideWithBorder(HandleBorderCollision(borderBot));
}

void Ball::CollideWithPaddle(Vector2 direction)
{
	mVelX = direction.x();
	mVelY = direction.y();
}

void Ball::CollideWithBorder(Vector2 direction)
{
	mVelX = direction.x();
	mVelY = direction.y();
}

Vector2 Ball::HandlePaddleCollision(const Paddle& paddle)
{
	Vector2 paddlePos{ paddle.GetPosition() };
	double paddleTop{ paddlePos.y() };
	double paddleBot{ paddlePos.y() + paddle.GetHeight() };
	double paddleLeft{ paddlePos.x() };
	double paddleRight{ paddlePos.x() + paddle.GetWidth() };

	double ballTop{ mPosition.y() };
	double ballBot{ mPosition.y() + mHeight };
	double ballLeft{ mPosition.x() };
	double ballRight{ mPosition.x() + mWidth };

	Vector2 ballDir{ mVelX, mVelY }; // basically these values acts as direction coordinates

	if (ballBot < paddleTop) return ballDir;
	if (ballTop > paddleBot) return ballDir;
	if (ballLeft > paddleRight) return ballDir;
	if (ballRight < paddleLeft) return ballDir;

	// translating from contact by 5.0 pixels to avoid "sticking"
	mPosition += Vector2((ballDir.x() > 0.0 ? -5.0 : 5.0), ballDir.y());

	double ballMid{ (ballTop + ballBot) / 2 };
	double paddleMid{ (paddleTop + paddleBot) / 2 };

	double changeY{ 0.0 };
	if (ballMid <= paddleTop)
	{
		changeY = -1.0;
	}
	else if (ballMid >= paddleBot)
	{
		changeY = 1.0;
	}
	else if (ballMid < paddleMid || ballMid > paddleMid)
	{
		changeY = (ballMid - paddleMid) / (paddleMid - paddleTop);
	}
	else
	{
		changeY = 0.0f;
	}

	// play beep sound
	Mix_PlayChannel(-1, gAudioBeep, 0);

	// calculation for ball's angled movement
	double ballAngle{ std::atan(changeY) };
	double changeX{ ballDir.x() > 0 ? -std::cos(ballAngle) : std::cos(ballAngle) };

	ballDir = Vector2(changeX, changeY);

	if (BALL_SPEED == INITIAL_SPEED)
	{
		BALL_SPEED = FINAL_SPEED;
	}

	return ballDir;
}

Vector2 Ball::HandleBorderCollision(const Border& border)
{
	Vector2 borderPos{ border.GetPosition() };
	double borderTop{ borderPos.y() };
	double borderBot{ borderPos.y() + border.GetHeight() };
	double borderLeft{ borderPos.x() };
	double borderRight{ borderPos.x() + border.GetWidth() };

	double ballTop{ mPosition.y() };
	double ballBot{ mPosition.y() + mHeight };
	double ballLeft{ mPosition.x() };
	double ballRight{ mPosition.x() + mWidth };

	Vector2 ballDir{ mVelX, mVelY }; // basically these values acts as direction coordinates

	if (ballBot < borderTop) return ballDir;
	if (ballTop > borderBot) return ballDir;
	if (ballLeft > borderRight) return ballDir;
	if (ballRight < borderLeft) return ballDir;

	// play plop sound
	Mix_PlayChannel(-1, gAudioPlop, 0);

	// translating from contact by 5.0 pixels to avoid "sticking"
	mPosition += Vector2(ballDir.x(), (ballDir.y() > 0.0 ? -5.0 : 5.0));
	// border will just reflect projection of ball
	ballDir = Vector2(ballDir.x(), ballDir.y() * -1);

	return ballDir;
}

void Ball::Reset(Vector2 newPos)
{
	mPosition = newPos;
	// change direction of new ball
	mVelX *= -1;
	BALL_SPEED = INITIAL_SPEED;
}

void Ball::HandleOutOfBound(Vector2 newPos, Score& score)
{
	// check for which bound has ball crossed
	if (mPosition.x() < 0.0)
	{
		// play peep sound
		Mix_PlayChannel(-1, gAudioPeep, 0);
		// player 1 wins
		Reset(newPos);
		score.IncrementScore(false);
	}
	else if (mPosition.x() > SCREEN_WIDTH)
	{
		// play peep sound
		Mix_PlayChannel(-1, gAudioPeep, 0);
		// player 2 wins
		Reset(newPos);
		score.IncrementScore(true);
	}
} 

void Ball::Render()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_Rect ball_rect = { mPosition.x(), mPosition.y(), mWidth, mHeight };
	SDL_RenderFillRect(gRenderer, &ball_rect);
}