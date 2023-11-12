#include "Engine/States/Level.h"
#include <string>

MapleEngine::Level::Level()
{
}

MapleEngine::Level::~Level()
{
}

MapleEngine::Entity* MapleEngine::Level::GetEntityByID(UInt ID)
{
	std::map<UInt, UniquePtr<Entity>>::iterator pos = m_entities.find(ID);
	if (pos != m_entities.end())
	{
		return pos->second.get();
	}
	else
	{
		std::cout << "No Entity with ID: " + std::to_string(ID) + " could be found!" << std::endl;
		return nullptr;
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

UInt MapleEngine::Level::GetNewID()
{
	UInt randomID = rand();

	// Will loop to find a ID that isn't taken already in the Level.
	while (GetEntityByID(randomID) == nullptr)
	{
		randomID = rand();
	}

	return randomID;
}
