#pragma once
#include "Engine/States/Level.h"

namespace Echelon
{
	class TestLevel : public MapleEngine::Level
	{
		// Inherited via Level
		void InitializeLevel() override;
		void Update(float dt) override;
		void Render() override;
	};
}