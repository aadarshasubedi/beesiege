#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "SingletonObj.h"
#include <NiSmartPointer.h>
#include <NiPhysXProp.h>
#include <list>
#include <NiNode.h>
#include "Queen.h"

class GameObj3d;
NiSmartPointer(GameObj3d);
class NiPhysXScene;
NiSmartPointer(NiPhysXScene);

class GameManager : public SingletonObj<GameManager>
{
	friend SingletonObj<GameManager>;
public:

	bool Init(NiNodePtr parent, NiPhysXScenePtr physXScene);
	void UpdateAll(float fTime);
	bool AddObject(GameObj3dPtr object, NiNodePtr parent);
	bool AddObject(GameObj3dPtr object, NiNodePtr parent, NiPhysXScenePtr physXScene);
	void AddAgent(AgentPtr agent);
	void RemoveObject(GameObj3dPtr object);

	inline QueenPtr GetQueen() const  { return m_spQueen; }
	inline const std::list<AgentPtr>& GetAgents() const { return m_lAgents; }

private:

	GameManager();
	~GameManager();

	std::list<GameObj3dPtr> m_lObjects;
	std::list<AgentPtr> m_lAgents;
	QueenPtr m_spQueen;
};

#endif