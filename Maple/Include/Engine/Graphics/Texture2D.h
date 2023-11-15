#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "Engine/Utils/Commons.h"

class SDL_Texture;

namespace MapleEngine
{
	class ENGINE_API Texture2D
	{
	private:
		SDL_Texture* m_pTexture;
		std::string m_texturePath;

		int m_width;
		int m_height;
		uint32_t m_format;

	public:
		Texture2D(SDL_Texture* texture, std::string path);
		~Texture2D();

		void Free();

		operator SDL_Texture* () const { return m_pTexture; }

		/* Returns the raw SDL texture */
		SDL_Texture& GetRawTexture() { return *m_pTexture; }

		/* Returns the Asset Path to this Texture */
		std::string GetTexturePath() { return m_texturePath; }

		UInt GetWidth() { return m_width; }
		UInt GetHeight() { return m_height; }

		/* Returns the Memory Size of this Texture in KB */
		UInt GetTextureMemorySize();
	};
}
