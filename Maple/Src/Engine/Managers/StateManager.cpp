#include "Engine/Managers/StateManager.h"
#include "Engine/Utils/Commons.h"

MapleEngine::StateManager* MapleEngine::StateManager::m_rInstance;

MapleEngine::StateManager& MapleEngine::StateManager::GetInstance()
{
	return *m_rInstance;
}

MapleEngine::StateManager::StateManager()
{
	m_rInstance = this;
	m_pState = nullptr;
}

MapleEngine::StateManager::~StateManager()
{
	// Delete all States 
	for (UInt i = 0; i < m_states.size(); i++)
	{
		m_states[i].reset();
	}

	m_states.clear();
	m_pState = nullptr;
}

void MapleEngine::StateManager::UpdateState(float dt)
{
	if (IsStateLoaded())
	{
		m_pState->Update(dt);
	}
}

void MapleEngine::StateManager::RenderState()
{
	if (IsStateLoaded())
	{
		m_pState->Render();
	}
}
