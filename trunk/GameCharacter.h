#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "GameObj3d.h"
#include "Agent.h"

class GameCharacter : public GameObj3d
{
public:
	GameCharacter(ResourceManager::ResourceType type);
	virtual ~GameCharacter();

	inline AgentPtr GetAgent() const {return m_spAgent;}
	inline void SetTarget (GameCharacter* target) {m_pTarget = target;}
	inline void SetTempTargetPos(const NxVec3& pos)
	{m_vTempTargetPos = pos;}
protected:

	virtual void DoExtraUpdates(float fTime)=0;
	virtual bool DoExtraInits();
	AgentPtr m_spAgent;
	GameCharacter* m_pTarget;
	NxVec3 m_vTempTargetPos;
};

NiSmartPointer(GameCharacter);

#endif