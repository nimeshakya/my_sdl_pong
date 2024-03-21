#pragma once

#include <SDL.h>

#include "GameWindow.h"
#include "Vector2.h"

class Paddle
{
public:
	const int PADDLE_SPEED{ 400 };
	Paddle() : mPosition{ 0, 0 }, mWidth{ UNIT_LEN }, mHeight{ UNIT_LEN * 5 }, mVelY{ 0 } {}
	Paddle(double posX, double posY) : mPosition{ posX, posY }, mWidth{ UNIT_LEN }, mHeight{ UNIT_LEN * 5 }, mVelY{ 0 } {}

	// update all states (for now, positions)
	void Update(double deltaTime);
	void HandleMovement(bool isPlayer1);

	void Render();

	Vector2 GetPosition() const { return mPosition; }
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
private:
	Vector2 mPosition;
	int mWidth;
	int mHeight;
	double mVelY;
};