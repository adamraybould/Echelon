#include "Game/Levels/TestLevel.h"

Echelon::TestLevel::TestLevel()
{
}

Echelon::TestLevel::~TestLevel()
{
}

void Echelon::TestLevel::InitializeLevel()
{
	player = &CreateEntity<Player>();
	slime = &CreateEntity<Slime>();
}

void Echelon::TestLevel::Update(float dt)
{
	Level::Update(dt);
}

void Echelon::TestLevel::Render()
{
	Level::Render();
}
