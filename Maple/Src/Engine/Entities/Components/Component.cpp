#include <Engine/Entities/Components/Component.h>
#include "Engine/Entities/Entity.h"

MapleEngine::Component::Component(Entity& entity) : m_rOwner(entity)
{
	SetActive(true);
}