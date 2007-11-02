/**
 * Holds game objects and updates them. Singleton class.
 */
#include "GameManager.h"
#include "GameObj3d.h"
#include "ResourceManager.h"
#include "Bee.h"
#include "ConfigurationManager.h"
#include "LevelManager.h"
#include <NiPhysXScene.h>
#include <NiApplication.h>

//------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
GameManager::GameManager() : m_fDeltaTime(0.0f)
{
}
//------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
GameManager::~GameManager()
{
	m_lObjects.RemoveAll();
	m_lAgents.RemoveAll();
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

	// create queen
	m_spQueen = NiNew Queen;
	if (!AddObject((GameObj3dPtr)m_spQueen, parent, physXScene))
	{
		return false;
	}
	m_spQueen->GetAgent()->GetActor()->setGlobalPosition(NxVec3(0.0, 100.0, -200.0));


	if (!LevelManager::Get()->LoadLevel(1))
	{
		return false;
	}

	m_spCurrentLevel = LevelManager::Get()->GetLevel(1);
	
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
	for (int i=0; i<m_lObjects.GetSize(); i++)
	{
		GameObj3dPtr obj = m_lObjects.Get(it);
		obj->Update(fTime);
		it = m_lObjects.GetNextPos(it);
	}

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
 */
void GameManager::AddAgent(AgentPtr agent)
{
	m_lAgents.AddTail(agent);
}
//------------------------------------------------------------------------ 
/** 
 * Adds an enemy to the enemies list
 * 
 * @param enemy
 */
void GameManager::AddEnemy(GameCharacterPtr enemy)
{
	m_lEnemies.AddTail(enemy);
}
//------------------------------------------------------------------------ 
/**
* Initilizes an enemy
* @param enemy
* @return bool
*/
bool GameManager::CreateEnemy(GameCharacterPtr enemy)
{	
	return AddObject((GameObj3d*)enemy, m_pGameApplication->GetScene(),
		m_pGameApplication->GetPhysXScene());
}
//------------------------------------------------------------------------ 
/** 
 * Removes an enemy from the enemy list
 * 
 * @param enemy
 */
void GameManager::RemoveEnemy(GameCharacterPtr enemy)
{
	m_lEnemies.Remove(enemy);
}
//------------------------------------------------------------------------ 
/** 
 * Removes an object from the list
 * 
 * @param object
 */
void GameManager::RemoveObject(GameObj3dPtr object)
{
	m_lObjects.Remove(object);
}
//------------------------------------------------------------------------
