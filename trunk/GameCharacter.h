#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "GameObj3d.h"
#include "Agent.h"
#include <NiTMap.h>
#include "CharacterAttribute.h"

class GameCharacter : public GameObj3d
{
	NiDeclareRTTI;

public:

	enum AttributeType
	{
		ATTR_CONTROLLER,
		ATTR_HEALTH
	};

	GameCharacter(ResourceManager::ResourceType type);
	virtual ~GameCharacter();
	
	NxActor* GetActor() const {return m_pActor;}
	void AddAttribute (AttributeType type, CharacterAttributePtr attr)
	{ m_tAttributes.SetAt(type, attr); }
	CharacterAttribute* GetAttribute(AttributeType type);


protected:

	virtual void DoExtraUpdates(float fTime)=0;
	virtual bool DoExtraInits();
	
	NxActor* m_pActor;
	NiTMap<AttributeType, CharacterAttributePtr> m_tAttributes;
};

NiSmartPointer(GameCharacter);

#endif