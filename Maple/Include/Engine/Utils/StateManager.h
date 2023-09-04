#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include <vector>
#include <iostream>

namespace MapleEngine
{
	class ENGINE_API IState
	{
	public:
		virtual ~IState() = default;

		virtual void Initialize() = 0;
		virtual void Update(float dt) = 0;
		virtual void Render() = 0;
	};

	class ENGINE_API StateManager
	{
	private: 
		static StateManager* m_rInstance;

		IState* m_rState;
		std::vector<IState*> m_states;

	public:
		static StateManager& GetInstance();

		StateManager();
		~StateManager();

		void UpdateState(float dt);
		void RenderState();

		template <typename T>
		void LoadState()
		{
			if (GetState<T>() != nullptr)
			{
				m_rState = nullptr;
				m_rState = GetState<T>();
			}
			else
			{
				std::cout << "No State called " << typeid(T).name() << " was found. Creating one." << std::endl;
				T* state = new T();
				m_states.push_back(state);
				m_rState = state;	
			}

			// Initialize State
			m_rState->Initialize();
		}

		template <typename T>
		IState* GetState()
		{
			static_assert(std::is_base_of<IState, T>::value, "T must be a subclass of IState");

			for (auto i = m_states.begin(); i != m_states.end(); i++)
			{
				T* state = dynamic_cast<T*>(&**i);
				if (state != nullptr)
				{
					return state;
				}
			}

			std::cout << "Unable to find Registered State: " << typeid(T).name() << std::endl;
			return nullptr;
		}

		bool IsStateLoaded() { return m_rState != nullptr; }
	};
}