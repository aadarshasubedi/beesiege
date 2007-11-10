#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "GameObj3d.h"
#include "Agent.h"

class FSMAIControl;

class GameCharacter : public GameObj3d
{
public:
	GameCharacter(ResourceManager::ResourceType type);
	virtual ~GameCharacter();

	AgentPtr GetAgent() const {return m_spAgent;}
	void SetTarget (GameCharacter* target) {m_pTarget = target;}
	void SetTempTargetPos(const NxVec3& pos)
	{m_vTempTargetPos = pos;}
	GameCharacter* GetTarget() const {return m_pTarget;}
protected:

	virtual void DoExtraUpdates(float fTime)=0;
	virtual bool DoExtraInits();
	AgentPtr m_spAgent;
	GameCharacter* m_pTarget;
	NxVec3 m_vTempTargetPos;
	FSMAIControl* m_pAIControl;
};

NiSmartPointer(GameCharacter);

#endif