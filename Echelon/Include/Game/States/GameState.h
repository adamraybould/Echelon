#pragma once
#include <Engine/Managers/StateManager.h>
#include "Game/Entities/Player.h"
#include "Game/Entities/Slime.h"

using namespace MapleEngine;

namespace Echelon
{
	class GameState : public MapleEngine::IState
	{
	private:
		Player* player;
		Slime* slime;

	public:
		GameState();
		~GameState();

		void Initialize() override;
		void Update(float dt) override;
		void Render() override;

	};
}
