#include "Level.h"
#include "GameManager.h"
//-----------------------------------------------------------------------------
Level::Level(const char* name) : m_pName(name)
{
}
//-----------------------------------------------------------------------------
Level::~Level()
{
	m_lEnemies.RemoveAll();
}
//-----------------------------------------------------------------------------
void Level::AddEnemy(GameCharacterPtr enemy, const NxVec3& pos)
{
	GameManager::Get()->AddEnemy(enemy);
	enemy->GetAgent()->GetActor()->setGlobalPosition(pos);
	m_lEnemies.AddTail(enemy);
}
//-----------------------------------------------------------------------------