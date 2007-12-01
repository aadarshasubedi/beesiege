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

	// the possible attribute types that
	// a character may have
	enum AttributeType
	{
		ATTR_CONTROLLER,
		ATTR_HEALTH,
		ATTR_ARMOR,
		ATTR_DAMAGE,
		ATTR_SOUND
	};

	// ctor / dtor
	GameCharacter(ResourceManager::ResourceType type);
	virtual ~GameCharacter();
	
	// adds an attribute to the attributes hash table
	void AddAttribute (AttributeType type, CharacterAttributePtr attr)
	{
		m_tAttributes.SetAt(type, attr); 
	}
	// getters / setters
	NxActor* GetActor() const {return m_pActor;}
	CharacterAttribute* GetAttribute(AttributeType type);


protected:

	// extra updates and initializations
	virtual void DoExtraUpdates(float fTime);
	virtual bool DoExtraInits();
	
	// the character's PhysX actor
	NxActor* m_pActor;
	// a hash table that contains all the character's attributes
	NiTMap<AttributeType, CharacterAttributePtr> m_tAttributes;

	// health billboard (debugging)
	NiNodePtr healthBill;
};

NiSmartPointer(GameCharacter);

#endif