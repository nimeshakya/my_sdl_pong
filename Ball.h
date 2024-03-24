#pragma once

#include <SDL.h>
#include "Vector2.h"
#include "GameWindow.h"
#include "GameAudio.h"
#include "Border.h"
#include "Paddle.h"
#include "Score.h"

class Ball
{
public:
	Ball() : INITIAL_SPEED{ 300 }, FINAL_SPEED{ 1000 }, BALL_SPEED{ 300 }, mPosition{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, mWidth{ UNIT_LEN }, mHeight{ UNIT_LEN }, mVelX{ 1.0 }, mVelY{ 0.0 } {}
	Ball(Vector2 pos) :  INITIAL_SPEED{ 300 }, FINAL_SPEED{ 500 }, BALL_SPEED{ 300 }, mPosition{ pos.x(), pos.y() }, mWidth{ UNIT_LEN }, mHeight{ UNIT_LEN }, mVelX{ 1.0 }, mVelY{ 0.0 } {}

	void Update(double deltaTime);
	void HandleCollision(const Paddle& paddle1, const Paddle& paddle2, const Border& borderTop, const Border& borderBot);
	// collide with paddle and return ball direction(?)
	// actually returns a vector after some calculations respective to point of contact
	void CollideWithPaddle(Vector2 direction);
	void CollideWithBorder(Vector2 direction);
	Vector2 HandlePaddleCollision(const Paddle& paddle);
	Vector2 HandleBorderCollision(const Border& border);
	void Reset(Vector2 newPos);
	// if ball go beyond screen (also update scoring)
	void HandleOutOfBound(Vector2 newPos, Score& score);

	void Render();

private:
	double BALL_SPEED;
	double INITIAL_SPEED;
	double FINAL_SPEED;
	Vector2 mPosition;
	int mWidth;
	int mHeight;
	double mVelX, mVelY;
};