#include "Engine/Utils/StateManager.h"
#include "Engine/Commons.h"

MapleEngine::StateManager* MapleEngine::StateManager::m_rInstance;

MapleEngine::StateManager& MapleEngine::StateManager::GetInstance()
{
	return *m_rInstance;
}

MapleEngine::StateManager::StateManager()
{
	m_rInstance = this;
	m_rState = nullptr;
}

MapleEngine::StateManager::~StateManager()
{
	// Delete all States 
	for (UInt i = 0; i < m_states.size(); i++)
	{
		IState* state = m_states[i];
		delete state;
	}

	m_states.clear();
	m_rState = nullptr;
}

void MapleEngine::StateManager::UpdateState(float dt)
{
	if (IsStateLoaded())
	{
		m_rState->Update(dt);
	}
}

void MapleEngine::StateManager::RenderState()
{
	if (IsStateLoaded())
	{
		m_rState->Render();
	}
}
