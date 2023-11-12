#pragma once
#include <Engine/Managers/StateManager.h>
#include "Game/Levels/TestLevel.h"

using namespace MapleEngine;

namespace Echelon
{
	class GameState : public MapleEngine::IState
	{
	private:
		UniquePtr<TestLevel> m_pLevel;

	public:
		GameState();
		~GameState();

		void Initialize() override;
		void Update(float dt) override;
		void Render() override;

	};
}
