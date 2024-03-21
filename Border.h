#pragma once
#include "GameWindow.h"
#include "Vector2.h"

class Border
{
public:
	Border() : mPosition{ 0, 0 }, mWidth{ SCREEN_WIDTH }, mHeight{ UNIT_LEN } {}
	Border(double posX, double posY) : mPosition{ posX, posY }, mWidth{ SCREEN_WIDTH }, mHeight{ UNIT_LEN } {}

	void Render();
private:
	Vector2 mPosition;
	int mWidth;
	int mHeight;
};