#ifndef LEVEL_H
#define LEVEL_H

#include "GameObj.h"
#include <NiTPointerList.h>
#include "Enemy.h"

class Level : public GameObj
{
public:
	// ctor / dtor
	Level(const char* name);
	~Level();

	// adds an enemy to the list
	bool AddEnemy(EnemyPtr enemy, const NxVec3& pos);

	// getters
	const NiTPointerList<EnemyPtr>& GetEnemies() const
	{
		return m_lEnemies; 
	}
	const char* GetName() const 
	{
		return m_pName;
	}
private:

	// a list that contains the level's enemies
	NiTPointerList<EnemyPtr> m_lEnemies;
	// the level's name
	const char *m_pName;
};

NiSmartPointer(Level);

#endif