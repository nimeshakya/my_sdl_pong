#pragma once

#include <SDL.h>
#include "Vector2.h"
#include "GameWindow.h"
#include "Border.h"
#include "Paddle.h"

class Ball
{
public:
	const int BALL_SPEED{ 500 };
	Ball() : mPosition{ 0, 0 }, mWidth{ UNIT_LEN }, mHeight{ UNIT_LEN }, mVelX{ 1.0 }, mVelY{ 0.0 } {}
	Ball(Vector2 pos) : mPosition{ pos.x(), pos.y() }, mWidth{ UNIT_LEN }, mHeight{ UNIT_LEN }, mVelX{ 1.0 }, mVelY{ 0.0 } {}

	void Update(double deltaTime);
	void HandleCollision(const Paddle& paddle1, const Paddle& paddle2, const Border& borderTop, const Border& borderBot);
	// collide with paddle and return ball direction(?)
	// actually returns a vector after some calculations respective to point of contact
	void CollideWithPaddle(Vector2 direction);
	void CollideWithBorder(Vector2 direction);
	Vector2 HandlePaddleCollision(const Paddle& paddle);
	Vector2 HandleBorderCollision(const Border& border);

	void Render();

private:
	Vector2 mPosition;
	int mWidth;
	int mHeight;
	double mVelX, mVelY;
};