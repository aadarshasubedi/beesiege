#ifndef CHARACTERATTRIBUTE_H
#define CHARACTERATTRIBUTE_H

#include "GameObj.h"

class GameCharacter;

class CharacterAttribute : public GameObj
{
public:

	CharacterAttribute(GameCharacter* owner);
	virtual ~CharacterAttribute();

	virtual void Update(float fTime) = 0;

	GameCharacter* GetOwner() const {return m_pOwner;}

protected:

	GameCharacter* m_pOwner;
};

NiSmartPointer(CharacterAttribute);

#endif