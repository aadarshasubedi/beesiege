#include "LevelManager.h"
#include "tinyXML/tinyXML.h"
#include <NiApplication.h>
#include "Locust.h"
#include <string>
using namespace std;
//------------------------------------------------------------------------------
LevelManager::LevelManager()
{
}
//------------------------------------------------------------------------------
LevelManager::~LevelManager()
{
	m_lLevels.RemoveAll();
}
//------------------------------------------------------------------------------
bool LevelManager::LoadLevel(unsigned int id)
{
	char file[20];
	sprintf_s(file, "data/level%d.xml", id);
	
	TiXmlDocument doc(NiApplication::ConvertMediaFilename(file));
	
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		TiXmlElement* root = doc.RootElement();
		if (root)
		{
			const char* name = root->Attribute("name");
			if (name)
			{
				LevelPtr level = NiNew Level(name);
				if (ReadEnemies(root->FirstChildElement("enemies"), level))
				{
					m_lLevels.SetAt(id, level);
					return true;
				}
			}
		}
	}
	
	return false;

}
//------------------------------------------------------------------------
bool LevelManager::ReadFloat(float &value, TiXmlElement* node, const char* child)
{
	TiXmlElement* current = node->FirstChildElement(child);
	if (current)
	{
		value    = (float)atof(current->GetText());
	}
	else 
	{
		return false;
	}

	return true;
}
//------------------------------------------------------------------------
bool LevelManager::ReadEnemies(TiXmlElement* node, LevelPtr level)
{
	if (!node) return false;
	TiXmlElement* current = node->FirstChildElement();
	for (current = node->FirstChildElement(); current; current = current->NextSiblingElement())
	{
		const char* enemyType = current->Attribute("type");
		if (enemyType)
		{
			if (!strcmp(enemyType, "LOCUST"))
			{
				LocustPtr enemy = NiNew Locust;
				float x, y, z;
				if (ReadFloat(x, current, "x") && 
					ReadFloat(y, current, "y") && 
					ReadFloat(z, current, "z"))
				{
					enemy->GetAgent()->GetActor()->setGlobalPosition(NxVec3(x, y, z));
				//	level->AddEnemy((GameCharacter*)enemy);
				}
			}
		}
	}

	return false;
}