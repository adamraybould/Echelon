#pragma once
#include <Engine/Entities/Entity.h>

using namespace MapleEngine;
namespace Echelon
{
	class Slime : public Entity
	{
	public:
		Slime(UInt ID);

		void Update(float dt) override;
		void Render() override;
	};
}