#ifndef LEVEL_H
#define LEVEL_H

#include "GameObj.h"
#include <NiTPointerList.h>
#include "Enemy.h"

class Level : public GameObj
{
public:
	Level(const char* name);
	~Level();
	bool AddEnemy(EnemyPtr enemy, const NxVec3& pos);
	inline const NiTPointerList<EnemyPtr>& GetEnemies() const
	{ return m_lEnemies; }
	inline const char* GetName() const {return m_pName;}
private:

	NiTPointerList<EnemyPtr> m_lEnemies;
	const char *m_pName;
};

NiSmartPointer(Level);

#endif