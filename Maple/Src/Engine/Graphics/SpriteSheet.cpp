#include "Engine/Graphics/SpriteSheet.h"
#include "Engine/Managers/AssetManager.h"
#include <iostream>

MapleEngine::SpriteSheet::SpriteSheet(Texture2D& texture, int spriteWidth, int spriteHeight) : m_pTextureAtlas(texture)
{
	m_spriteWidth = spriteWidth;
	m_spriteHeight = spriteHeight;
	m_spriteCount = (m_pTextureAtlas.GetWidth() / m_spriteWidth) + (m_pTextureAtlas.GetHeight() / m_spriteHeight);
}

MapleEngine::SpriteSheet::~SpriteSheet()
{
	// Is already destroyed in Sprite
	//delete &m_pTextureAtlas;
}

void MapleEngine::SpriteSheet::AddAnimation(Animation& animation)
{
	m_animations.insert(std::make_pair(animation.Name, animation));
}

MapleEngine::Animation* MapleEngine::SpriteSheet::GetAnimation(const char* name)
{
	std::map<std::string, Animation>::iterator pos = m_animations.find(name);
	if (pos != m_animations.end())
		return &pos->second;

	std::cout << "No Animation called " << name << " could be found." << std::endl;
	return nullptr;
}

Rectangle MapleEngine::SpriteSheet::GetSprite(UInt index)
{
	int maxXIndex = m_pTextureAtlas.GetWidth() / m_spriteWidth;
	int xFramePos = (index % maxXIndex) * m_spriteWidth;
	int yFrameIndex = (int)(index / maxXIndex);
	int yFramePos = yFrameIndex * m_spriteHeight;

	return Rectangle(xFramePos, yFramePos, m_spriteWidth, m_spriteHeight);
}
