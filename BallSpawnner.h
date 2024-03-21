#pragma once
#include <vector>
#include "GameWindow.h"
#include "Vector2.h"
// the middle line of board
// also the positions where ball will spawn
class BallSpawnner
{
public:
	BallSpawnner();

	void Render();
private:
	std::vector<Vector2> mSpawnPositions;
};