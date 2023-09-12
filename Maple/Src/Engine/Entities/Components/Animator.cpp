#include "Engine/Entities/Components/Animator.h"

MapleEngine::Animator::Animator(Entity& entity, SpriteRenderer& spriteRenderer, SpriteSheet& spriteSheet) : Component(entity), m_rSpriteRenderer(spriteRenderer), m_rSpriteSheet(spriteSheet)
{
	m_speed = 100.0f;
	CurrentAnimation = nullptr;
	m_frame = 0;
	m_frameTimer = 0.0f;
}

void MapleEngine::Animator::Initialize()
{
}

void MapleEngine::Animator::Update(float dt)
{
	if (CurrentAnimation == nullptr)
		return;

	m_frameTimer += dt;
	if (m_frameTimer >= m_speed)
	{
		if (m_frame >= CurrentAnimation->GetLastIndex())
			m_frame = CurrentAnimation->GetStartIndex();

		m_frame++;
		m_frameTimer = 0.0f;

		m_rSpriteRenderer.GetSprite()->SetSpriteSource(m_rSpriteSheet.GetSprite(m_frame));
	}
}

void MapleEngine::Animator::Render()
{
	if (CurrentAnimation == nullptr)
		return;
}

void MapleEngine::Animator::Destroy()
{
}

void MapleEngine::Animator::SetAnimation(const char* name)
{
	if (CurrentAnimation != nullptr && CurrentAnimation->Name == name)
		return;

	Animation* newAnimation = m_rSpriteSheet.GetAnimation(name);
	if (newAnimation != nullptr)
	{
		CurrentAnimation = newAnimation;
		m_frame = CurrentAnimation->GetStartIndex();
		m_frameTimer = m_speed;
	}
}
