#include "Paddle.h"

void Paddle::Update(double deltaTime)
{
	mPosition += Vector2(0, mVelY) * PADDLE_SPEED * deltaTime;
}

void Paddle::HandleMovement(bool isPlayer1)
{
	// scan key event handle for continuous key presses
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (isPlayer1)
	{
		// pressed key is 'W' and position y not above UNIT_LEN (borderTop's bottom)
		if (currentKeyStates[SDL_SCANCODE_W] && !(mPosition.y() < UNIT_LEN))
		{
			mVelY = -1.0;
		}
		else if (currentKeyStates[SDL_SCANCODE_S] && !(mPosition.y() + mHeight > SCREEN_HEIGHT - UNIT_LEN))
		{
			mVelY = 1.0;
		}
		else
		{
			mVelY = 0.0;
		}
	}
	else
	{
		// pressed key is 'Up arrow' and position y not above UNIT_LEN (borderTop's bottom)
		if (currentKeyStates[SDL_SCANCODE_UP] && !(mPosition.y() < UNIT_LEN))
		{
			mVelY = -1.0;
		}
		else if (currentKeyStates[SDL_SCANCODE_DOWN] && !(mPosition.y() + mHeight > SCREEN_HEIGHT - UNIT_LEN))
		{
			mVelY = 1.0;
		}
		else
		{
			mVelY = 0.0;
		}
	}
}

void Paddle::Render()
{
	SDL_SetRenderDrawColor(gRenderer, GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE, 0xFF);
	SDL_Rect paddle_rect{ mPosition.x(), mPosition.y(), mWidth, mHeight };
	SDL_RenderFillRect(gRenderer, &paddle_rect);
}
