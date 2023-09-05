#pragma once
#include "Engine/Managers/StateManager.h"
#include <Engine/Entities/Entity.h>

using namespace MapleEngine;

namespace Echelon
{
	class GameState : public MapleEngine::IState
	{
	private:
		Entity* player;

	public:
		GameState();

		void Initialize() override;
		void Update(float dt) override;
		void Render() override;
	};
}
