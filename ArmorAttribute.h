#ifndef ARMORATTRIBUTE_H
#define ARMORATTRIBUTE_H

#include "CharacterAttribute.h"

class GameCharacter;

class ArmorAttribute : public CharacterAttribute
{
public:

	// ctor / dtor
	ArmorAttribute(GameCharacter* owner);
	~ArmorAttribute();

	// updates the attribute
	void Update(float fTime);

	// gets armor
	const float GetArmor() const
	{
		return m_fArmor;
	}
private:
	
	// armor amount
	float m_fArmor;
	// the max distance from the queen so that armor is
	// greater than zero
	const float m_fcMaxQueenDistance;
};

NiSmartPointer(ArmorAttribute);

#endif