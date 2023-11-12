#include "Game/Levels/TestLevel.h"

Echelon::TestLevel::TestLevel()
{
	CreateEntity<Player>();
	CreateEntity<Slime>();
}

Echelon::TestLevel::~TestLevel()
{
}

void Echelon::TestLevel::InitializeLevel()
{

}

void Echelon::TestLevel::Update(float dt)
{
	Level::Update(dt);
}

void Echelon::TestLevel::Render()
{
	Level::Render();
}
