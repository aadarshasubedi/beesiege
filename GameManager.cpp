#include "GameManager.h"
#include "GameObj3d.h"
#include "ResourceManager.h"
#include <NiPhysXScene.h>
#include "Bee.h"
#include <NiApplication.h>
#include "ConfigurationManager.h"
using namespace std;


//------------------------------------------------------------------------
GameManager::GameManager() : m_fDeltaTime(0.0f)
{
}
//------------------------------------------------------------------------
GameManager::~GameManager()
{
	list<GameObj3dPtr>::iterator it;
	for (it = m_lObjects.begin(); it != m_lObjects.end(); it++)
	{
		(*it) = 0;
	}
	m_lObjects.clear();

	list<AgentPtr>::iterator it2;
	for (it2 = m_lAgents.begin(); it2 != m_lAgents.end(); it2++)
	{
		(*it2) = 0;
	}
	m_lAgents.clear();

	m_spQueen = 0;

	m_lEnemies.RemoveAll();
	ConfigurationManager::Destroy();
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
	if (AddObject((GameObj3dPtr)m_spQueen, parent, physXScene))
	{
		return true;
	}


	
	return false;
}
//------------------------------------------------------------------------
void GameManager::UpdateAll(float fTime)
{
	m_fDeltaTime = m_pGameApplication->GetFrameTime();
	list<GameObj3dPtr>::iterator it;
	for (it = m_lObjects.begin(); it != m_lObjects.end(); it++)
	{
		(*it)->Update(fTime);
	}

}
//------------------------------------------------------------------------
bool GameManager::AddObject(GameObj3dPtr object, NiNodePtr parent)
{
	if (object->Init(parent))
	{
		m_lObjects.push_back(object);
		return true;
	}
	
	return false;
}
//------------------------------------------------------------------------
bool GameManager::AddObject(GameObj3dPtr object, NiNodePtr parent, NiPhysXScenePtr physXScene)
{
	if (object->Init(parent, physXScene))
	{
		m_lObjects.push_back(object);
		return true;
	}
	
	return false;
}
//------------------------------------------------------------------------
void GameManager::AddAgent(AgentPtr agent)
{
	m_lAgents.push_back(agent);
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
	m_lObjects.remove(object);
}
