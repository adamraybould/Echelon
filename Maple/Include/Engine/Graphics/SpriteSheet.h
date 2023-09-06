#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "Engine/Graphics/Texture2D.h"
#include "Animation.h"
#include <map>

struct Rectangle;

namespace MapleEngine
{
	class ENGINE_API SpriteSheet
	{
	private:
		Texture2D& m_pTextureAtlas;

		UInt m_spriteWidth;
		UInt m_spriteHeight;
		UInt m_spriteCount;

		std::map<std::string, Animation> m_animations;

	public:
		SpriteSheet(Texture2D& texture, int spriteWidth, int spriteHeight);
		~SpriteSheet();

		void AddAnimation(Animation& animation);

		/* Returns a Animation assigned to the Sprite Sheet. Will return nullptr if there isn't one */
		Animation* GetAnimation(const char* name);

		/* Returns a Rect for a Sprite in the Sprite Sheet */
		Rectangle GetSprite(UInt index);

		/* Returns the Width of a Sprite */
		UInt GetSpriteWidth() { return m_spriteWidth; }

		/* Returns the Height of a Sprite */
		UInt GetSpriteHeight() { return m_spriteHeight; }

		/* Returns the number of Sprites within the Sprite Sheet */
		UInt GetSpriteCount() { return m_spriteCount; }

		/* Returns the Full Texture of the Sprite Sheet */
		Texture2D& GetTextureAtlas() { return m_pTextureAtlas; }
	};
}