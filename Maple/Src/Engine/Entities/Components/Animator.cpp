#include "Engine/Entities/Components/Animator.h"

MapleEngine::Animator::Animator(Entity& entity, SpriteRenderer& spriteRenderer, SpriteSheet& spriteSheet) : Component(entity), m_rSpriteRenderer(spriteRenderer), m_rSpriteSheet(spriteSheet)
{
	m_speed = 100.0f;
	m_pCurrentAnimation = nullptr;
	m_frame = 0;
	m_frameTimer = 0.0f;
}

void MapleEngine::Animator::Initialize()
{
}

void MapleEngine::Animator::Update(float dt)
{
	if (m_pCurrentAnimation == nullptr)
		return;

	m_frameTimer += dt;
	if (m_frameTimer >= m_speed)
	{
		if (m_frame >= m_pCurrentAnimation->GetLastIndex())
			m_frame = m_pCurrentAnimation->GetStartIndex();

		m_frame++;
		m_frameTimer = 0.0f;

		m_rSpriteRenderer.GetSprite()->SetSpriteSource(m_rSpriteSheet.GetSprite(m_frame));
	}
}

void MapleEngine::Animator::Render()
{
	if (m_pCurrentAnimation == nullptr)
		return;
}

void MapleEngine::Animator::Destroy()
{
}

void MapleEngine::Animator::SetAnimation(const char* name)
{
	m_pCurrentAnimation = m_rSpriteSheet.GetAnimation(name);
	m_frame = m_pCurrentAnimation->GetStartIndex();
	m_frameTimer = m_speed;
}
