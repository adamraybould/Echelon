#include "Engine/Entities/Entity.h"

MapleEngine::Entity::Entity(UInt64 ID)
{
	m_ID = ID;
}

MapleEngine::Entity::~Entity()
{
	RemoveAllComponents();
}

void MapleEngine::Entity::Update(float dt)
{
	for (UInt i = 0; i < m_components.size(); i++)
	{
		Component& component = *m_components[i];
		if (component.IsActive())
		{
			component.Update(dt);
		}
	}
}

void MapleEngine::Entity::Render()
{
	for (UInt i = 0; i < m_components.size(); i++)
	{
		Component& component = *m_components[i];
		if (component.IsActive())
		{
			component.Render();
		}
	}
}

void MapleEngine::Entity::RemoveAllComponents()
{
	for (UInt i = 0; i < m_components.size(); i++)
	{
		m_components[i].reset();
	}

	m_components.clear();
}