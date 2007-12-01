#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "SingletonObj.h"
#include <NiSmartPointer.h>
#include <NiPhysXProp.h>
#include <NiNode.h>
#include <NiTPointerList.h>
#include "Queen.h"
#include "Enemy.h"
#include "GameApp.h"
#include "Level.h"
#include "ResourceManager.h"

class GameObj3d;
NiSmartPointer(GameObj3d);
class NiPhysXScene;
NiSmartPointer(NiPhysXScene);

// template class that copies two NiTPointer lists
template <class T>
void CopyLists (const NiTPointerList<T> &from, NiTPointerList<T> &to)
{
	to.RemoveAll();
	NiTListIterator it = from.GetHeadPos();
	for (unsigned int i=0; i<from.GetSize(); i++)
	{
		to.AddTail(from.Get(it));
		it = from.GetNextPos(it);
	}
}

// Singleton class
class GameManager : public SingletonObj<GameManager>
{
	friend SingletonObj<GameManager>;
public:

	// initializes the manager
	bool Init(NiNodePtr parent, NiPhysXScenePtr physXScene, NiApplication* app);
	// updates all objects
	void UpdateAll(float fTime);
	// creates a GameObj3d depending on the type
	GameObj3dPtr CreateObject3d (ResourceManager::ResourceType type);
	// records kill
	void RecordKill();

	// getters / setters
	void ResetAgentGroup()
	{
		m_plAgents = 0;
	}
	void SetAgentGroup (const NiTPointerList<AgentPtr>* agents)
	{
		m_plAgents = agents;
	}
	QueenPtr GetQueen() const 
	{
		return m_spQueen; 
	}
	const NiTPointerList<AgentPtr>& GetAgents() const 
	{ 
		return *m_plAgents; 
	}
	GameApp* GetGameApp() const
	{
		return m_pGameApplication;
	}
	const NiTPointerList<EnemyPtr>& GetEnemies() const 
	{
		return m_lEnemies;
	}
	const float GetDeltaTime() const
	{
		return m_fDeltaTime;
	}
	void SetStrongAttack(bool value)
	{
		if (m_spCurrentTarget)
		{
			m_spCurrentTarget->SetStrongAttack(value);
		}
	}
	void SetCurrentTarget (EnemyPtr enemy)
	{
		m_spCurrentTarget = enemy;
	}

	EnemyPtr GetCurrentTarget() const
	{
		return m_spCurrentTarget;
	}

	
private:

	// private ctor / dtor
	GameManager();
	~GameManager();

	// initializs and adds a GameObj3d to the objects list
	bool AddObject(GameObj3dPtr object, NiNodePtr parent);
	// overloaded function
	bool AddObject(GameObj3dPtr object, NiNodePtr parent, NiPhysXScenePtr physXScene);
	// removes an object from the list
	void RemoveObject(GameObj3dPtr object);
	// removes an enemy from the list
	void RemoveEnemy(EnemyPtr enemy);

	// object, agent and enemy lists
	NiTPointerList<GameObj3dPtr> m_lObjects;
	NiTPointerList<EnemyPtr>     m_lEnemies;
	const NiTPointerList<AgentPtr>*    m_plAgents;
	
	// the main queen that the player controls
	QueenPtr m_spQueen;
	// the game application that contains our NIF scene and
	// our PhysX scene
	GameApp* m_pGameApplication;
	// delta time
	float    m_fDeltaTime;
	// max height until fog becomes thicker
	float    m_fMaxPlayerHeight;
	// default fog depth
	float    m_fDefaultFogDepth;
	// used to calculate fog when the player exceeds a 
	// certain height
	float    m_fFogScaleValue;
	// the current game level
	LevelPtr m_spCurrentLevel;
	// current enemy target
	EnemyPtr m_spCurrentTarget;
	// the player's killing rate
	float m_fKillingRate;
	// the player's kill count
	float m_fKillCount;
	// the last time the player killed something
	float m_fLastKillTime;
};

#endif