#pragma once
#include "GameWindow.h"
#include "Vector2.h"

class Paddle
{
public:
	Paddle() : mPosition{ 0, 0 }, mWidth{ UNIT_LEN }, mHeight{ UNIT_LEN * 5 } {}
	Paddle(double posX, double posY) : mPosition{ posX, posY }, mWidth{ UNIT_LEN }, mHeight{ UNIT_LEN * 5 } {}

	void Render();
private:
	Vector2 mPosition;
	int mWidth;
	int mHeight;
};