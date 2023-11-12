#pragma once
#include "Engine/States/Level.h"
#include "Game/Entities/Player.h"
#include "Game/Entities/Slime.h"

namespace Echelon
{
	class TestLevel : public MapleEngine::Level
	{
	private:

	public:
		TestLevel();
		~TestLevel();

		// Inherited via Level
		void InitializeLevel() override;
		void Update(float dt) override;
		void Render() override;
	};
}