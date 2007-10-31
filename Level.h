#ifndef LEVEL_H
#define LEVEL_H

#include "GameObj.h"
#include <NiTPointerList.h>
#include "GameCharacter.h"

class Level : public GameObj
{
public:
	Level(const char* name);
	~Level();

	void AddEnemy(GameCharacterPtr enemy, const NxVec3& pos);
	inline const NiTPointerList<GameCharacterPtr>& GetEnemies() const
	{ return m_lEnemies; }
	inline const char* GetName() const {return m_pName;}
private:

	NiTPointerList<GameCharacterPtr> m_lEnemies;
	const char *m_pName;
};

NiSmartPointer(Level);

#endif