#ifndef CHARACTERATTRIBUTE_H
#define CHARACTERATTRIBUTE_H

#include "GameObj.h"

class GameCharacter;

class CharacterAttribute : public GameObj
{
	NiDeclareRTTI;
public:

	// ctor / dtor
	CharacterAttribute(GameCharacter* owner);
	virtual ~CharacterAttribute();
	// pure virtual: updates the attribute
	virtual void Update(float fTime) = 0;
	// getters
	GameCharacter* GetOwner() const {return m_pOwner;}

protected:
	// the attribute's owner
	GameCharacter* m_pOwner;
};

NiSmartPointer(CharacterAttribute);

#endif