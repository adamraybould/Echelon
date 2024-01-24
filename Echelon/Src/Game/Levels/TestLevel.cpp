#include "Game/Levels/TestLevel.h"
#include "Game/World Gen/Block.h"

Echelon::TestLevel::TestLevel()
{
}

Echelon::TestLevel::~TestLevel()
{
}

void Echelon::TestLevel::InitializeLevel()
{
	player = &CreateEntity<Player>();
}

void Echelon::TestLevel::Update(float dt)
{
	Level::Update(dt);
}

void Echelon::TestLevel::Render()
{
	Level::Render();
}
