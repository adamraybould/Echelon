#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "Engine/Graphics/Texture2D.h"
#include "Engine/Graphics/SpriteSheet.h"
#include <map>

struct SDL_Renderer;

namespace MapleEngine
{
	class ENGINE_API AssetManager
	{
	private:
		static SDL_Renderer* m_pRenderer;

		// A List of Sprite Sheets Created
		static std::map<std::string, SpriteSheet*> m_spriteSheets;

	public:
		AssetManager(SDL_Renderer& renderer);
		~AssetManager();

		/* Loads and returns a 2D Texture. Returns a error texture if failed. */
		static Texture2D& LoadTexture(const char* path);

		/* Loads and returns a Sprite Sheet from a .SF file. Returns a error texture if failed */
		static SpriteSheet& LoadSpriteSheet(const char* path, const char* sheetName);

	private:
		static bool CheckAssetManagerInitialized();
	};
}