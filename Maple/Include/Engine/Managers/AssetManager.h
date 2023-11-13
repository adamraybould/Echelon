#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "Engine/Graphics/Texture2D.h"
#include "Engine/Graphics/SpriteSheet.h"
#include "Engine/Utils/Commons.h"
#include <map>

namespace MapleEngine
{
	class ENGINE_API AssetManager
	{
	public:
		static MultiCastEvent<void, Texture2D*> OnTextureLoaded;

	private:
		static std::map<std::string, UniquePtr<SpriteSheet>> m_loadedSpriteSheets;
		static std::vector<UniquePtr<Texture2D>> m_loadedTextures;

	public:
		~AssetManager();

		/* Loads and returns a 2D Texture. Returns a error texture if failed. */
		static Texture2D& LoadTexture(const char* path);

		/* Loads and returns a Sprite Sheet from a .SF file. Returns a error texture if failed */
		static SpriteSheet& LoadSpriteSheet(const char* path, const char* sheetName);

	private:
		static bool CheckAssetManagerInitialized();
	};
}