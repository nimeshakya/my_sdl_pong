#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

constexpr int SCREEN_WIDTH{ 640};
constexpr int SCREEN_HEIGHT{ 480 };
constexpr int UNIT_LEN{ 15 };

// Global Golour for game objects
namespace GameObjColor
{
	constexpr Uint8 BG_RED{ 0x2B };
	constexpr Uint8 BG_GREEN{ 0x2B };
	constexpr Uint8 BG_BLUE{ 0x2B };

	constexpr Uint8 OB_RED{ 0xD2 };
	constexpr Uint8 OB_GREEN{ 0xD2 };
	constexpr Uint8 OB_BLUE{ 0xD2 };
}

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;