#include "GameManager.h"
#include "GameObj3d.h"
#include "ResourceManager.h"
#include <NiPhysXScene.h>
#include "Bee.h"
using namespace std;

//------------------------------------------------------------------------
GameManager::GameManager()
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
}
//------------------------------------------------------------------------
bool GameManager::Init(NiNodePtr parent, NiPhysXScenePtr physXScene)
{
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
void GameManager::RemoveObject(GameObj3dPtr object)
{
	m_lObjects.remove(object);
}
//------------------------------------------------------------------------