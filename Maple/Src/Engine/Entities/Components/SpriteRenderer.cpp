#include "Engine/Entities/Components/SpriteRenderer.h"
#include "Engine/Main/Application.h"
#include <SDL_image.h>
#include <SDL.h>

MapleEngine::SpriteRenderer::SpriteRenderer(Entity& entity) : Component(entity)
{
	m_pSprite = nullptr;
	m_flip = SDL_FLIP_NONE;
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

	SDL_RenderCopyEx(&Application::GetInstance().GetRenderer(), m_pSprite->GetTexture(), &src, &dest, ownerT.Rotation, NULL, (SDL_RendererFlip)m_flip);
}

void MapleEngine::SpriteRenderer::Destroy()
{
	m_pSprite.reset();
}

void MapleEngine::SpriteRenderer::SetSprite(Texture2D& texture)
{
	m_pSprite = std::make_unique<Sprite>(texture);
}

void MapleEngine::SpriteRenderer::SetSprite(SpriteSheet& spriteSheet)
{
	m_pSprite = std::make_unique<Sprite>(spriteSheet);
}

void MapleEngine::SpriteRenderer::SetFlip(bool value)
{
	m_flip = value ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}
