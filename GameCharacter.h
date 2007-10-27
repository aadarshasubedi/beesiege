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
	inline void SetTarget (const NxVec3& target) {m_vTarget = target;}
protected:

	virtual void DoExtraUpdates(float fTime)=0;
	virtual bool DoExtraInits();
	AgentPtr m_spAgent;
	NxVec3 m_vTarget;
};

NiSmartPointer(GameCharacter);

#endif