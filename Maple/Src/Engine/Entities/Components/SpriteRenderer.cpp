#include "Engine/Entities/Components/SpriteRenderer.h"
#include "Engine/Main/Application.h"
#include <SDL_image.h>

MapleEngine::SpriteRenderer::SpriteRenderer(Entity& entity) : Component(entity)
{
	m_pSprite = nullptr;
}

void MapleEngine::SpriteRenderer::Initialize()
{
}

void MapleEngine::SpriteRenderer::Update(float dt)
{
}

void MapleEngine::SpriteRenderer::Render()
{
	if (m_pSprite == nullptr)
		return;

	Transform ownerT = GetOwner().Transform;
	
	SDL_Rect dest = { ownerT.Position.X, ownerT.Position.Y, m_pSprite->GetSource().Width * ownerT.Scale.X, m_pSprite->GetSource().Height * ownerT.Scale.Y };
	SDL_Rect src = { m_pSprite->GetSource().X, m_pSprite->GetSource().Y, m_pSprite->GetSource().Width, m_pSprite->GetSource().Height };

	SDL_RenderCopyEx(Application::GetInstance().GetRenderer(), m_pSprite->GetTexture(), &src, &dest, ownerT.Rotation, m_pSprite->GetOrigin(), SDL_FLIP_NONE);
}

void MapleEngine::SpriteRenderer::Destroy()
{
	delete m_pSprite;
}

void MapleEngine::SpriteRenderer::SetSprite(Sprite& sprite)
{
	m_pSprite = &sprite;
}
