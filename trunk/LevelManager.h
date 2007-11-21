#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "SingletonObj.h"
#include <NiTMap.h>
#include "Level.h"

class TiXmlElement;

// Singleton Class
class LevelManager : public SingletonObj<LevelManager>
{
	friend SingletonObj<LevelManager>;
public:
	// loads a level with the given id
	bool LoadLevel(unsigned int id);
	// gets a level from the hash table
	LevelPtr GetLevel(unsigned int id) const;
private:
	// private ctor / dtor
	LevelManager();
	~LevelManager();

	// readers for certain XML nodes
	bool ReadFloat(float &value, TiXmlElement* node, const char* child);
	bool ReadEnemies(TiXmlElement* node, LevelPtr level);

	// the hash table that contains the game's levels
	NiTMap<unsigned int, LevelPtr> m_tLevels;


};

#endif