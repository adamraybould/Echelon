#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "Texture2D.h"
#include "SpriteSheet.h"

struct SDL_Rect;
struct SDL_Point;
struct Rectangle;

namespace MapleEngine
{
	class ENGINE_API Sprite
	{
	private:
		Texture2D& m_rTexture;

		Rectangle m_source;
		Vector2 m_origin;

	public:
		Sprite(Texture2D& texture);
		Sprite(SpriteSheet& spriteSheet);
		~Sprite();

		void SetSpriteSource(Rectangle rect);

		Texture2D& GetTexture() { return m_rTexture; }
		Rectangle& GetSource() { return m_source; }
		Vector2& GetOrigin() { return m_origin; }
	};
}