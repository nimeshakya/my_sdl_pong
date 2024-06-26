#include "BallSpawnner.h"

BallSpawnner::BallSpawnner()
{
	int loop_max{ SCREEN_HEIGHT - UNIT_LEN };
	int count{ 0 }; // count to alternate the spawnning of spawnner
	int posX{ (SCREEN_WIDTH - UNIT_LEN) / 2 };
	for (int i = UNIT_LEN; i < loop_max; ++i, ++count)
	{
		if (i % UNIT_LEN == 0 && count % 2 == 0)
		{
			mSpawnPositions.push_back(Vector2(posX, i));
		}
	}
}

void BallSpawnner::Render()
{
	SDL_SetRenderDrawColor(gRenderer, GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE, 0xFF);
	for (auto position : mSpawnPositions)
	{
		SDL_Rect spawn_rect{ position.x(), position.y(), UNIT_LEN, UNIT_LEN };
		SDL_RenderFillRect(gRenderer, &spawn_rect);
	}
}

Vector2 BallSpawnner::GetSpawnPosition()
{
	// random number generator
	std::mt19937_64 generator(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count())); // random number generator engine
	std::uniform_int_distribution<int> distribution{ 0, (int)mSpawnPositions.size() - 1 }
	;
	return mSpawnPositions[distribution(generator)];
}

std::vector<Vector2> BallSpawnner::GetAllSpawnPositions()
{
	return mSpawnPositions;
}