#pragma once
#include <Engine/Entities/Entity.h>

using namespace MapleEngine;
namespace Echelon
{
	class Player : public Entity
	{
	public:
		Player(UInt ID);

		void Update(float dt) override;
		void Render() override;
	};
}