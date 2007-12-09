/**
 * Holds game objects and updates them. Singleton class.
 */

#include <iostream>
#include <sstream>
#include <string>
#include "GameManager.h"
#include "GameObj3d.h"
#include "Bee.h"
#include "Locust.h"
#include "ConfigurationManager.h"
#include "TextManager.h"
#include "LevelManager.h"
#include <NiPhysXScene.h>
#include <NiApplication.h>
#include "EnemyBase.h"
#include "Flower.h"
using namespace std;
//------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
GameManager::GameManager() : 
m_fDeltaTime(0.0f), m_plAgents(0), m_pCurrentTarget(0),
m_fKillingRate(0.0f), m_fKillCount(0.0f), m_fLastKillTime(0.0f),
m_spAmbientSounds(0)
{
}
//------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
GameManager::~GameManager()
{

	if (m_spAmbientSounds)
	{
		m_spAmbientSounds->Stop();
		m_spAmbientSounds = 0;
	}
	m_lObjects.RemoveAll();
	m_lEnemies.RemoveAll();
	m_lFlowers.RemoveAll();
	m_spQueen = 0;
	m_spCurrentLevel = 0;
	ConfigurationManager::Destroy();
	LevelManager::Destroy();
}
//------------------------------------------------------------------------ 
/** 
 * Initializes manager
 * 
 * @param parent
 * @param physXScene
 * @param app
 * 
 * @return bool
 */
bool GameManager::Init(NiNodePtr parent, NiPhysXScenePtr physXScene, NiSample* app )
{
	// read configuration file
	m_pGameApplication = (GameApp*)app;
	if (!ConfigurationManager::Get()->ReadConfigurationFile(
		NiSample::ConvertMediaFilename("data/configuration.xml")))
	{
		NiMessageBox("Could Not Read Configuration File", "Error");
		return false;
	}

	m_fMaxPlayerHeight = ConfigurationManager::Get()->queen_maxHeight;
	m_fDefaultFogDepth = ConfigurationManager::Get()->scene_fogDefaultDepth;
	m_fFogScaleValue   = ConfigurationManager::Get()->queen_fogScaleValue;

	// create queen
	m_spQueen = NiNew Queen;
	if (!AddObject((GameObj3dPtr)m_spQueen, parent, physXScene))
	{
		return false;
	}
	m_spQueen->GetActor()->setGlobalPosition(NxVec3(0.0, 100.0, -200.0));


	if (!LevelManager::Get()->LoadLevel(1))
	{
		return false;
	}

	//m_spCurrentLevel = LevelManager::Get()->GetLevel(1);
	//CopyLists(m_spCurrentLevel->GetEnemies(), m_lEnemies);

	if (!AddObject((GameObj3dPtr)(NiNew EnemyBase), parent))
	{
		return false;
	}
	
	// Create all the flowers in the scene
	CreateFlowers(parent);

	m_spAmbientSounds = ResourceManager::Get()->GetSound(
		ResourceManager::RES_SOUND_AMBIENT, 0);
	if (m_spAmbientSounds)
	{
		m_spAmbientSounds->Play();
	}
	return true;
}
//------------------------------------------------------------------------
/**
*Creates all the flowers and tranlates them to its position in the scene
*/
void GameManager::CreateFlowers(NiNodePtr parent)
{	
	for(int i=1;i<20;i++)
	{
		stringstream s;
		s << i;
		string str1 = "attachmentBox" + s.str();
		char* c = new char[str1.length()];
		strcpy(c,str1.c_str());
		NiFixedString s1 = c;
		NiNode* attacher1 = (NiNode*) parent->GetObjectByName(s1);
		FlowerPtr flower = (Flower*)(GameObj3d*)CreateObject3d(ResourceManager::RES_MODEL_FLOWER);
		flower->GetNode()->SetTranslate(attacher1->GetTranslate());
	}
}

//------------------------------------------------------------------------ 
/** 
 * Updates all game objects
 * 
 * @param fTime
 */
void GameManager::UpdateAll(float fTime)
{
	m_fDeltaTime = m_pGameApplication->GetFrameTime();
	NiTListIterator it = m_lObjects.GetHeadPos();
	int size = m_lObjects.GetSize();
	for (int i=0; i<size; i++)
	{
		GameObj3dPtr obj = m_lObjects.Get(it);
		if (!obj) break;
		if (!obj->IsActive())
		{
			if (NiIsKindOf(Enemy, obj))
			{
				EnemyPtr enemy = (Enemy*)(GameObj3d*)obj;
				RemoveEnemy(enemy);
			}
			RemoveObject(obj);
			it = m_lObjects.GetNextPos(it);
			continue;
		}
		obj->Update(fTime);
		it = m_lObjects.GetNextPos(it);
	}

	// if queen goes too high then increse fog significantly so 
	// the player cannot see anything. This will make him want to 
	// go back to a normal height where we want him.
	NiFogProperty* fog = (NiFogProperty*)m_pGameApplication->GetScene()->GetProperty(NiProperty::FOG);
	if (fog)
	{
		float y = GetQueen()->GetActor()->getGlobalPosition().y; 
		if ( y >= m_fMaxPlayerHeight)
		{
			//fog->SetDepth(y*y*y/m_fFogScaleValue);	
		}
		else
		{
			fog->SetDepth(m_fDefaultFogDepth);
		}
	}
}
//------------------------------------------------------------------------ 
/**
* Creates a 3d object of a given type and returns 
* that object to the caller
* @param ResourceManager::ResourceType: the type
*/
GameObj3dPtr GameManager::CreateObject3d(ResourceManager::ResourceType type)
{
	NiNodePtr mainScene = m_pGameApplication->GetScene();
	NiPhysXScenePtr physxScene = m_pGameApplication->GetPhysXScene();
	GameObj3dPtr obj = 0;
	switch (type)
	{
	case ResourceManager::RES_MODEL_BEE:
			obj = NiNew Bee;
			if (!AddObject(obj, mainScene, physxScene))
			{
				obj = 0;
			}
			break;
	case ResourceManager::RES_MODEL_QUEEN:
			obj = NiNew Queen;
			if (!AddObject(obj, mainScene, physxScene))
			{
				obj = 0;
			}
			break;
	case ResourceManager::RES_MODEL_LOCUST:
			obj = NiNew Locust;
			if (!AddObject(obj, mainScene, physxScene))
			{
				obj = 0;
			}
			m_lEnemies.AddTail((Enemy*)(GameObj3d*)obj);
			break;
	case ResourceManager::RES_MODEL_FLOWER:
		obj = NiNew Flower;
			if (!AddObject(obj, mainScene))
			{
				obj = 0;
			}
			m_lFlowers.AddTail((Flower*)(GameObj3d*)obj);
			break;
	default:
		return 0;
	}

	return obj;
}
//------------------------------------------------------------------------ 
/**
* Increases kill count, and calculates killing rate
*/
void GameManager::RecordKill()
{
	float killingInterval = m_pGameApplication->GetAccumTime() -
		m_fLastKillTime;

	m_fLastKillTime = m_pGameApplication->GetAccumTime();

	m_fKillCount += 1.0f;
	m_fKillingRate += (killingInterval - m_fKillingRate)/ m_fKillCount;

	char rate[50];
	sprintf_s(rate, "rate: %f", m_fKillingRate);
	TextManager::Get()->UpdateText(TextManager::STRING_KILLINGRATE, rate); 
}
//------------------------------------------------------------------------ 
/** 
 * Adds an object to the list
 * 
 * @param object
 * @param parent
 * 
 * @return bool
 */
bool GameManager::AddObject(GameObj3dPtr object, NiNodePtr parent)
{
	if (object->Init(parent))
	{
		m_lObjects.AddTail(object);
		
		return true;
	}
	
	return false;
}
//------------------------------------------------------------------------ 
/** 
 * Adds a PhysX object to the list
 * 
 * @param object
 * @param parent
 * @param physXScene
 * 
 * @return bool
 */
bool GameManager::AddObject(GameObj3dPtr object, NiNodePtr parent, NiPhysXScenePtr physXScene)
{
	if (object->Init(parent, physXScene))
	{
		m_lObjects.AddTail(object);
		
		return true;
	}
	
	return false;
}
//------------------------------------------------------------------------ 
/** 
 * Removes an object from the list
 * 
 * @param object
 */
void GameManager::RemoveObject(GameObj3dPtr object)
{
	if (!m_lObjects.IsEmpty())
	{
		// remove physx prop and actor from scene
		NiPhysXPropPtr prop = object->GetProp();
		if (prop)
		{
			prop->DetachSceneCallback(m_pGameApplication->GetPhysXScene());
			if (NiIsKindOf(GameCharacter, object))
			{
				((GameCharacter*)(GameObj3d*)object)->ResetActor(0);
			}
		}

		// remove scene node
		NiNode* parent = object->GetNode()->GetParent();
		if (parent)
			parent->DetachChild(object->GetNode());

		m_lObjects.Remove(object);
	}
	
}
//------------------------------------------------------------------------
/** 
 * Removes an agent from the list
 * 
 * @param agent
 *//*
void GameManager::RemoveAgent(AgentPtr agent)
{
	if (!m_lAgents.IsEmpty())
	{
		m_lAgents.Remove(agent);
	}
	
}
//------------------------------------------------------------------------
/** 
 * Removes an enemy from the list
 * 
 * @param agent
 */
void GameManager::RemoveEnemy(EnemyPtr enemy)
{
	if (!m_lEnemies.IsEmpty())
	{
		m_lEnemies.Remove(enemy);
	}
}
