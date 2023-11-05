#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include <map>

union SDL_Event;

namespace MapleEngine
{
	enum KeyState
	{
		KEY_UP,
		KEY_DOWN
	};

	enum class ENGINE_API Keys {
		A, B, C, D, E, F, G, H, I, J, K, L, M,
		N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		SPACE, CTRL, ALT, SHIFT
	};

	class ENGINE_API InputHandler
	{
	private:
		static std::map<Keys, KeyState> m_keyStates;
		static std::map<int, KeyState> m_mouseStates;

	public:
		InputHandler();
		~InputHandler();

		void HandleInput(SDL_Event& event);

		/* Returns if a Key is Pressed. */
		static bool IsKeyDown(Keys key);
	};
}