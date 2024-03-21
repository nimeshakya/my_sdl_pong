#pragma once
#include <vector>
#include <random>

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
	Vector2 GetSpawnPosition(std::mt19937_64 gen, std::uniform_int_distribution<int> distrib);
	std::vector<Vector2> GetAllSpawnPositions();
private:
	std::vector<Vector2> mSpawnPositions;
};