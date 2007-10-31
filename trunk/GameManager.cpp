#include "GameManager.h"
#include "GameObj3d.h"
#include "ResourceManager.h"
#include <NiPhysXScene.h>
#include "Bee.h"
#include <NiApplication.h>
#include "ConfigurationManager.h"
#include "LevelManager.h"

//------------------------------------------------------------------------
GameManager::GameManager() : m_fDeltaTime(0.0f)
{
}
//------------------------------------------------------------------------
GameManager::~GameManager()
{
	m_lObjects.RemoveAll();
	m_lAgents.RemoveAll();
	m_lEnemies.RemoveAll();
	m_spQueen = 0;
	ConfigurationManager::Destroy();
	//LevelManager::Destroy();
}
//------------------------------------------------------------------------
bool GameManager::Init(NiNodePtr parent, NiPhysXScenePtr physXScene, NiApplication* app )
{
	m_pGameApplication = (GameApp*)app;
	if (!ConfigurationManager::Get()->ReadConfigurationFile(
		NiApplication::ConvertMediaFilename("data/configuration.xml")))
	{
		NiMessageBox("Could Not Read Configuration File", "Error");
		return false;
	}
	
	m_spQueen = NiNew Queen;
	if (!AddObject((GameObj3dPtr)m_spQueen, parent, physXScene))
	{
		return false;
	}
	m_spQueen->GetAgent()->GetActor()->setGlobalPosition(NxVec3(0.0, 100.0, -200.0));


	//if (!LevelManager::Get()->LoadLevel(1))
	//{
	///	return false;
	//}
	
	return true;
}
//------------------------------------------------------------------------
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
void GameManager::AddAgent(AgentPtr agent)
{
	m_lAgents.AddTail(agent);
}
//------------------------------------------------------------------------
void GameManager::AddEnemy(GameCharacterPtr enemy)
{
	m_lEnemies.AddTail(enemy);
}
//------------------------------------------------------------------------
void GameManager::RemoveEnemy(GameCharacterPtr enemy)
{
	m_lEnemies.Remove(enemy);
}
//------------------------------------------------------------------------
void GameManager::RemoveObject(GameObj3dPtr object)
{
	m_lObjects.Remove(object);
}
//------------------------------------------------------------------------
