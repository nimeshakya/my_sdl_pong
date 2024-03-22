#pragma once
#include <vector>
#include <random>
#include <chrono>

#include "GameWindow.h"
#include "Vector2.h"
// the middle line of board
// also the positions where ball will spawn
class BallSpawnner
{
public:
	BallSpawnner();

	void Render();
	// returns random position from mSpawnPositions
	Vector2 GetSpawnPosition();
	std::vector<Vector2> GetAllSpawnPositions();
private:
	std::vector<Vector2> mSpawnPositions;
};