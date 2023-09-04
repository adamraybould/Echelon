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

	Transform ownerTransform = GetOwner().Transform();

	SDL_Rect rect;
	rect.x = ownerTransform.Position.X;
	rect.y = ownerTransform.Position.Y;
	rect.w = m_pSprite->GetTexture().GetSize().X * ownerTransform.Scale.X;
	rect.h = m_pSprite->GetTexture().GetSize().Y * ownerTransform.Scale.Y;

	SDL_RenderCopy(Application::GetInstance().GetRenderer(), m_pSprite->GetTexture().GetRawTexture(), NULL, &rect);
}

void MapleEngine::SpriteRenderer::Destroy()
{
	delete m_pSprite;
}

void MapleEngine::SpriteRenderer::SetSprite(Sprite& sprite)
{
	m_pSprite = &sprite;
}
