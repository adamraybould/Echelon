#include "Game/Entities/Components/PlayerMovement.h"
#include <Engine/Entities/Entity.h>
#include <Engine/Managers/InputHandler.h>
#include <Engine/Entities/Components/Animator.h>

Echelon::PlayerMovement::PlayerMovement(MapleEngine::Entity& entity) : MapleEngine::Component(entity)
{
	m_spriteRenderer = GetOwner().GetComponent<SpriteRenderer>();
	m_animator = GetOwner().GetComponent<Animator>();

	m_velocity = Vector2::Zero();
	m_movementSpeed = 0.3f;
}

void Echelon::PlayerMovement::Initialize()
{
}

void Echelon::PlayerMovement::Update(float dt)
{
	GetOwner().Transform.Position += m_velocity * dt;
	m_velocity = Vector2::Zero();

	if (InputHandler::IsKeyDown(Keys::W))
	{
		m_velocity = Vector2(m_velocity.X, -m_movementSpeed);
		m_animator->SetAnimation("run_Up");
	}
	else if (InputHandler::IsKeyDown(Keys::S))
	{
		m_velocity = Vector2(m_velocity.X, m_movementSpeed);
		m_animator->SetAnimation("run_Down");
	}

	if (InputHandler::IsKeyDown(Keys::A))
	{
		m_velocity = Vector2(-m_movementSpeed, m_velocity.Y);

		m_animator->SetAnimation("run_Side");
		m_spriteRenderer->SetFlip(true);
	}
	else if (InputHandler::IsKeyDown(Keys::D))
	{
		m_velocity = Vector2(m_movementSpeed, m_velocity.Y);

		m_animator->SetAnimation("run_Side");
		m_spriteRenderer->SetFlip(false);
	}

	if (m_velocity == Vector2::Zero())
		m_animator->SetAnimation("idle_Side");
}

void Echelon::PlayerMovement::Render()
{
}

void Echelon::PlayerMovement::Destroy()
{
}
