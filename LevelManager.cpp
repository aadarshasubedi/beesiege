/**
 * Loads game levels from an XML file. Sigleton Class.
 */

#include "LevelManager.h"
#include "tinyXML/tinyXML.h"
#include "Locust.h"
#include <NiApplication.h>
#include <string>
using namespace std;
//------------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
LevelManager::LevelManager()
{
}
//------------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
LevelManager::~LevelManager()
{
	m_tLevels.RemoveAll();
}
//------------------------------------------------------------------------------ 
/** 
 * Loads a level and puts it in the level hash table
 * 
 * @param id
 * 
 * @return bool
 */
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
					m_tLevels.SetAt(id, level);
					return true;
				}
			}
		}
	}
	
	return false;

}
//------------------------------------------------------------------------ 
/** 
 * Finds a level with the desired id and returns it
 * 
 * @param id
 * 
 * @return LevelPtr
 */
LevelPtr LevelManager::GetLevel(unsigned int id) const
{
	LevelPtr lvl = 0;
	m_tLevels.GetAt(id, lvl);

	return lvl;
}
//------------------------------------------------------------------------ 
/** 
 * Reads a float value form an XML file
 * 
 * @param value
 * @param node
 * @param child
 * 
 * @return bool
 */
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
/** 
 * Reads enemy node in the XML file
 * 
 * @param node
 * @param level
 * 
 * @return bool
 */
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
					if (!level->AddEnemy((GameCharacter*)enemy, NxVec3(x, y, z)))
						return false;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}