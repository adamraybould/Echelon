#include "Systems/StateSystem.h"

namespace Core::Systems
{
    StateSystem::StateSystem()
    {
        m_pCurrentState = nullptr;
    }

    StateSystem::~StateSystem()
    {
        // Delete States
        for (UInt i = 0; i < m_states.size(); i++)
        {
            m_states[i].reset();
        }

        m_states.clear();
        m_pCurrentState = nullptr;
    }

    void StateSystem::Initialize() const
    {
        for (UInt i = 0; i < m_states.size(); i++)
        {
            m_states[i]->Initialise();
        }
    }

    void StateSystem::Update(float delta) const
    {
        if (IsStateLoaded())
        {
            m_pCurrentState->Update(delta);
        }
    }
}
