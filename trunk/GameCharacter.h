#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "GameObj3d.h"
#include "Agent.h"

class GameCharacter : public GameObj3d
{
public:
	GameCharacter(ResourceManager::ResourceType type);
	virtual ~GameCharacter();

	AgentPtr GetAgent() const {return m_spAgent;}
protected:

	virtual void DoExtraUpdates(float fTime)=0;
	virtual bool DoExtraInits();
	AgentPtr m_spAgent;
};

NiSmartPointer(GameCharacter);

#endif