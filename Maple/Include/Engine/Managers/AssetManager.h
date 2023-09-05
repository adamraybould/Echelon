#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "Engine/Graphics/Texture2D.h"

struct SDL_Renderer;

namespace MapleEngine
{
	class ENGINE_API AssetManager
	{
	private:
		static SDL_Renderer* m_pRenderer;

	public:
		AssetManager(SDL_Renderer& renderer);
		~AssetManager();

		/* Loads and Returns a 2D Texture. Returns an error texture if failed. */
		static Texture2D& LoadTexture(const char* path);

	private:
		static bool CheckAssetManagerInitialized();
	};
}