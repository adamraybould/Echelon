#include "Engine/Managers/InputHandler.h"
#include <SDL.h>
#include <iostream>
using namespace MapleEngine;

std::map<Keys, KeyState> MapleEngine::InputHandler::m_keyStates;
std::map<int, KeyState> MapleEngine::InputHandler::m_mouseStates;

std::map<SDL_Keycode, Keys> keyMap =
{
	{ SDLK_a, Keys::A },
	{ SDLK_b, Keys::B },
	{ SDLK_c, Keys::C },
	{ SDLK_d, Keys::D },
	{ SDLK_e, Keys::E },
	{ SDLK_f, Keys::F },
	{ SDLK_g, Keys::G },
	{ SDLK_h, Keys::H },
	{ SDLK_i, Keys::I },
	{ SDLK_j, Keys::J },
	{ SDLK_k, Keys::K },
	{ SDLK_l, Keys::L },
	{ SDLK_m, Keys::M },
	{ SDLK_n, Keys::N },
	{ SDLK_o, Keys::O },
	{ SDLK_p, Keys::P },
	{ SDLK_q, Keys::Q },
	{ SDLK_r, Keys::R },
	{ SDLK_s, Keys::S },
	{ SDLK_t, Keys::T },
	{ SDLK_u, Keys::U },
	{ SDLK_v, Keys::V },
	{ SDLK_w, Keys::W },
	{ SDLK_x, Keys::X },
	{ SDLK_y, Keys::Y },
	{ SDLK_z, Keys::Z },
	{ SDLK_SPACE, Keys::SPACE }
};

MapleEngine::InputHandler::InputHandler()
{
	
}

MapleEngine::InputHandler::~InputHandler()
{

}

void MapleEngine::InputHandler::HandleInput(SDL_Event& event)
{
	Keys key = keyMap[event.key.keysym.sym];

	if (SDL_KEYDOWN == event.type)
		m_keyStates[key] = KeyState::KEY_DOWN;
	
	if (SDL_KEYUP == event.type)
		m_keyStates[key] = KeyState::KEY_UP;
}

bool MapleEngine::InputHandler::IsKeyDown(Keys key)
{
	return m_keyStates[key] == KeyState::KEY_DOWN;
}
