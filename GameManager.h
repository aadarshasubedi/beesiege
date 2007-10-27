#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "SingletonObj.h"
#include <NiSmartPointer.h>
#include <NiPhysXProp.h>
#include <list>
#include <NiNode.h>
#include <NiTPointerList.h>
#include "Queen.h"
#include "GameApp.h"
class GameObj3d;
NiSmartPointer(GameObj3d);
class NiPhysXScene;
NiSmartPointer(NiPhysXScene);


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
	void RemoveEnemy(GameCharacterPtr enemy);
	void RemoveObject(GameObj3dPtr object);
	
	inline QueenPtr GetQueen() const  { return m_spQueen; }
	inline const std::list<AgentPtr>& GetAgents() const { return m_lAgents; }
	inline GameApp* GetGameApp() const {return m_pGameApplication; }
	inline const NiTPointerList<GameCharacterPtr>& GetEnemies() const {return m_lEnemies;}
	inline const float GetDeltaTime() const {return m_fDeltaTime; }
private:

	GameManager();
	~GameManager();

	std::list<GameObj3dPtr> m_lObjects;
	std::list<AgentPtr> m_lAgents;
	NiTPointerList<GameCharacterPtr> m_lEnemies;

	QueenPtr m_spQueen;
	GameApp* m_pGameApplication;
	float    m_fDeltaTime;
};

#endif