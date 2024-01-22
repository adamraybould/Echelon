#include "Engine/States/Level.h"
#include <string>

MapleEngine::Level::Level()
{
	m_entityManager = std::make_unique<EntityManager>();
}

MapleEngine::Level::~Level()
{
	m_entityManager.reset();
}

void MapleEngine::Level::Update(float dt)
{
	std::map<UInt64, SharedPtr<Entity>>& entities = m_entityManager->GetEntityMap();
	for (auto i = entities.begin(); i != entities.end(); i++)
	{
		i->second->Update(dt);
	}
}

void MapleEngine::Level::Render()
{
	std::map<UInt64, SharedPtr<Entity>>& entities = m_entityManager->GetEntityMap();
	for (auto i = entities.begin(); i != entities.end(); i++)
	{
		i->second->Render();
	}
}

void MapleEngine::Level::DestroyEntity(Entity& entity)
{
	/*
	if (GetEntityByID(entity.GetID()) != nullptr)
	{
		delete &entity;
	}
	*/
}
