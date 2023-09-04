#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "SDL_image.h"
#include <Engine/Main/Application.h>
#include "Engine/Graphics/Texture2D.h"
#include <cstdio>

namespace MapleEngine
{
	Texture2D* LoadTexture(const char* path)
	{
		SDL_Renderer& renderer = Application::GetInstance().GetRenderer();
		SDL_Texture* texture = IMG_LoadTexture(&renderer, path);
		if (texture == nullptr)
		{
			printf("Texture could not be found!. SDL_Error: %s\n", SDL_GetError());
			return nullptr;
		}

		Texture2D* texture2D = new Texture2D(texture);
		return texture2D;
	}
}