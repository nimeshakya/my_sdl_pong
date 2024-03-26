#pragma once
#include "GameWindow.h"
#include "Vector2.h"

class Border
{
public:
	Border() : mPosition{ 0, 0 }, mWidth{ SCREEN_WIDTH }, mHeight{ UNIT_LEN } {}
	Border(double posX, double posY) : mPosition{ posX, posY }, mWidth{ SCREEN_WIDTH }, mHeight{ UNIT_LEN } {}

	void Render();

	Vector2 GetPosition() const { return mPosition; }
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
private:
	Vector2 mPosition;
	int mWidth;
	int mHeight;
};