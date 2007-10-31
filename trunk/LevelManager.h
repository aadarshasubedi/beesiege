#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "SingletonObj.h"
#include <NiTMap.h>
#include "Level.h"

class TiXmlElement;

class LevelManager : public SingletonObj<LevelManager>
{
	friend SingletonObj<LevelManager>;
public:
	
	bool LoadLevel(unsigned int id);
private:
	LevelManager();
	~LevelManager();
	bool ReadFloat(float &value, TiXmlElement* node, const char* child);
	bool ReadEnemies(TiXmlElement* node, LevelPtr level);

	NiTMap<unsigned int, LevelPtr> m_lLevels;


};

#endif