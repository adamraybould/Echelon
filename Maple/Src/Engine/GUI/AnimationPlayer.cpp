#include "Engine/GUI/AnimationPlayer.h"

MapleEngine::AnimationPlayer::AnimationPlayer()
{
	CurrentAnimation = nullptr;
	m_animationSpeed = 100.0f;
	m_frame = 0;
	m_frameCounter = 1;
	m_frameTimer = 0.0f;
}

MapleEngine::AnimationPlayer::AnimationPlayer(Animation* animation)
{
	CurrentAnimation = animation;
	m_animationSpeed = 100.0f;
	m_frame = 0;
	m_frameCounter = 1;
	m_frameTimer = 0.0f;
}

MapleEngine::AnimationPlayer::~AnimationPlayer()
{
	CurrentAnimation = nullptr;
}

void MapleEngine::AnimationPlayer::Update(float dt)
{
	if (CurrentAnimation == nullptr || CurrentAnimation->IsNull)
		return;

	m_frameTimer += dt;
	if (m_frameTimer >= m_animationSpeed)
	{
		if (m_frame >= CurrentAnimation->GetLastIndex())
		{
			m_frame = CurrentAnimation->GetStartIndex();
			m_frameCounter = 1;
		}

		m_frame++;
		m_frameCounter++;
		m_frameTimer = 0.0f;
	}
}

void MapleEngine::AnimationPlayer::SetAnimation(Animation& animation)
{
	CurrentAnimation = &animation;
	m_frame = CurrentAnimation->GetStartIndex();
	//m_frameTimer = m_animationSpeed;
}

