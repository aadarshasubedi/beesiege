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

class GameManager : public SingletonObj<GameManager>
{
	friend SingletonObj<GameManager>;
public:

	bool Init(NiNodePtr parent, NiPhysXScenePtr physXScene, NiApplication* app);
	void UpdateAll(float fTime);
	GameObj3dPtr CreateObject3d (ResourceManager::ResourceType type);
	void AddAgent(AgentPtr agent);
	
	QueenPtr GetQueen() const 
	{
		return m_spQueen; 
	}
	const NiTPointerList<AgentPtr>& GetAgents() const 
	{ 
		return m_lAgents; 
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
	
	void RemoveAgent(AgentPtr agent);
private:

	GameManager();
	~GameManager();

	bool AddObject(GameObj3dPtr object, NiNodePtr parent);
	bool AddObject(GameObj3dPtr object, NiNodePtr parent, NiPhysXScenePtr physXScene);
	void RemoveObject(GameObj3dPtr object);
	void RemoveEnemy(EnemyPtr enemy);

	NiTPointerList<GameObj3dPtr> m_lObjects;
	NiTPointerList<EnemyPtr>     m_lEnemies;
	NiTPointerList<AgentPtr>     m_lAgents;
	
	QueenPtr m_spQueen;
	GameApp* m_pGameApplication;
	float    m_fDeltaTime;
	float    m_fMaxPlayerHeight;
	float    m_fDefaultFogDepth;
	float    m_fFogScaleValue;
	LevelPtr m_spCurrentLevel;
};

#endif