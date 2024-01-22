#include "EntityManager.h"
#include <string>

MapleEngine::EntityManager::EntityManager()
{
}

MapleEngine::EntityManager::~EntityManager()
{
	for (auto i = m_entities.begin(); i != m_entities.end(); i++)
	{
		i->second.reset();
	}
	m_entities.clear();
}

void MapleEngine::EntityManager::DeleteEntity(UInt64 ID)
{
	Entity* entity = GetEntity(ID);
	if (entity != nullptr)
		m_entities.erase(ID);
}

MapleEngine::Entity* MapleEngine::EntityManager::GetEntity(UInt64 ID)
{
	std::map<UInt64, SharedPtr<Entity>>::iterator pos = m_entities.find(ID);
	if (pos != m_entities.end())
		return pos->second.get();
	else
	{
		std::cout << "No Entity with ID: " + std::to_string(ID) + " could be found!" << std::endl;
		return nullptr;
	}
}
