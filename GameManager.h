#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "SingletonObj.h"
#include <NiSmartPointer.h>
#include <NiPhysXProp.h>
#include <NiNode.h>
#include <NiTPointerList.h>
#include "Queen.h"
#include "GameApp.h"
#include "Level.h"

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
	bool AddObject(GameObj3dPtr object, NiNodePtr parent);
	bool AddObject(GameObj3dPtr object, NiNodePtr parent, NiPhysXScenePtr physXScene);
	void AddAgent(AgentPtr agent);
	void AddEnemy(GameCharacterPtr enemy);
	bool CreateEnemy(GameCharacterPtr enemy);
	void RemoveEnemy(GameCharacterPtr enemy);
	void RemoveObject(GameObj3dPtr object);
	
	inline QueenPtr GetQueen() const  { return m_spQueen; }
	inline const NiTPointerList<AgentPtr>& GetAgents() const { return m_lAgents; }
	inline GameApp* GetGameApp() const {return m_pGameApplication; }
	inline const NiTPointerList<GameCharacterPtr>& GetEnemies() const {return m_spCurrentLevel->GetEnemies();}
	inline const float GetDeltaTime() const {return m_fDeltaTime; }
	
private:

	GameManager();
	~GameManager();

	NiTPointerList<GameObj3dPtr> m_lObjects;
	NiTPointerList<AgentPtr> m_lAgents;
	NiTPointerList<GameCharacterPtr> m_lEnemies;

	QueenPtr m_spQueen;
	GameApp* m_pGameApplication;
	float    m_fDeltaTime;
	LevelPtr m_spCurrentLevel;
};

#endif