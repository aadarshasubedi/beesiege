/**
 * Holds game objects and updates them. Singleton class.
 */
#include "GameManager.h"
#include "GameObj3d.h"
#include "Bee.h"
#include "Locust.h"
#include "ConfigurationManager.h"
#include "LevelManager.h"
#include <NiPhysXScene.h>
#include <NiApplication.h>
#include "EnemyBase.h"
//------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
GameManager::GameManager() : m_fDeltaTime(0.0f), m_plAgents(0), m_spCurrentTarget(0)
{
}
//------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
GameManager::~GameManager()
{
	m_spCurrentTarget = 0;
	m_lObjects.RemoveAll();
	m_lEnemies.RemoveAll();
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
bool GameManager::Init(NiNodePtr parent, NiPhysXScenePtr physXScene, NiApplication* app )
{
	// read configuration file
	m_pGameApplication = (GameApp*)app;
	if (!ConfigurationManager::Get()->ReadConfigurationFile(
		NiApplication::ConvertMediaFilename("data/configuration.xml")))
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

	m_spCurrentLevel = LevelManager::Get()->GetLevel(1);
	CopyLists(m_spCurrentLevel->GetEnemies(), m_lEnemies);

	if (!AddObject((GameObj3dPtr)(NiNew EnemyBase), parent))
	{
		return false;
	}
	return true;
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
			//it = m_lObjects.GetNextPos(it);
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
	default:
		return 0;
	}

	return obj;
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
 * Adds an agent to the agent list
 * 
 * @param agent
 *//*
void GameManager::AddAgent(AgentPtr agent)
{
	m_lAgents.AddTail(agent);
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
		NiPhysXPropPtr prop = object->GetProp();
		if (prop)
		{
			prop->DetachSceneCallback(m_pGameApplication->GetPhysXScene());
		}

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