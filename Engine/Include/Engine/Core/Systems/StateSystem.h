#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include "Engine/Core/Singleton.h"
#include "Engine/Core/TypeDefs.h"

namespace Core
{
    class Renderer;

    namespace Systems
    {
        struct State
        {
        public:
            virtual ~State() = default;

            virtual void Initialize() = 0;
            virtual void Update(float delta) = 0;
            virtual void Render(Renderer& renderer) = 0;
        };

        class StateSystem : public Singleton<StateSystem>
        {
        private:
            State* m_pCurrentState;
            Array<SharedPtr<State>> m_states;

        public:
            StateSystem();
            ~StateSystem() override;

            void Initialize() const;
            void Update(float delta) const;
            void Render(Renderer& renderer) const;

            State& GetCurrentState() const { return *m_pCurrentState; }
            bool IsStateLoaded() const { return m_pCurrentState != nullptr; }

            template<typename T>
            bool AddState(bool load = false)
            {
                static_assert(std::is_base_of_v<State, T>, "T must be a subclass of State");

                // Check if State already exists
                for (UInt i = 0; i < m_states.size(); i++)
                {
                    if (typeid(m_states[i]) == typeid(T))
                        return false;
                }

                m_states.push_back(std::make_shared<T>());
                if (load)
                {
                    m_pCurrentState = m_states.back().get();
                }

                return true;
            }

            template<typename T>
            bool LoadState()
            {
                if (GetState<T>() != nullptr)
                {
                    m_pCurrentState = nullptr;
                    m_pCurrentState = GetState<T>();
                    return true;
                }

                return false;
            }

            template<typename T>
            State* GetState()
            {
                static_assert(std::is_base_of_v<State, T>, "T must be a subclass of State");

                for(auto i = m_states.begin(); i != m_states.end(); i++)
                {
                    T* state = dynamic_cast<T*>(&**i);
                    if (state != nullptr)
                        return state;
                }

                return nullptr;
            }
        };
    }
}

#endif //STATEMANAGER_H
