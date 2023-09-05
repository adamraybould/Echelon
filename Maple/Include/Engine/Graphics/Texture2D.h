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

		int m_width;
		int m_height;

	public:
		Texture2D(SDL_Texture& texture);
		~Texture2D();

		void Free();

		operator SDL_Texture* () const { return m_pTexture; }

		/* Returns the raw SDL texture */
		SDL_Texture* GetRawTexture() { return m_pTexture; }

		/* Returns a Vector2 with the Width and Height of the Texture */
		Vector2 GetSize() { return Vector2(m_width, m_height); }
	};
}
