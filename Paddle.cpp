#include "Paddle.h"

void Paddle::Render()
{
	SDL_SetRenderDrawColor(gRenderer, GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE, 0xFF);
	SDL_Rect paddle_rect{ mPosition.x(), mPosition.y(), mWidth, mHeight };
	SDL_RenderFillRect(gRenderer, &paddle_rect);
}