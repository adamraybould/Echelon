#include "Engine/Entities/Entity.h"

MapleEngine::Entity::Entity(UInt ID)
{
	m_ID = ID;
}

MapleEngine::Entity::~Entity()
{
}

void MapleEngine::Entity::Update(float dt)
{
	for (UInt i = 0; i < m_components.size(); i++)
	{
		Component* component = m_components[i];
		if (component->IsActive())
		{
			component->Update(dt);
		}
	}
}

void MapleEngine::Entity::Render()
{
	for (UInt i = 0; i < m_components.size(); i++)
	{
		Component* component = m_components[i];
		if (component->IsActive())
		{
			component->Render();
		}
	}
}

void MapleEngine::Entity::RemoveAllComponents()
{
	for (UInt i = 0; i < m_components.size(); i++)
	{
		m_components[i]->Destroy();
	}

	m_components.clear();
}