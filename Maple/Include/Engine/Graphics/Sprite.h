#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "Texture2D.h"

struct SDL_Rect;
struct SDL_Point;

namespace MapleEngine
{
	class ENGINE_API Sprite
	{
	private:
		Texture2D& m_rTexture;
		Vector2 m_origin;

	public:
		Sprite(Texture2D& texture);
		~Sprite();

		Texture2D& GetTexture() { return m_rTexture; }
	};
}