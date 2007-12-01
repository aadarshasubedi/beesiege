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

	// resets armor
	void Reset(float initialArmor);
	// increases armor
	void IncreaseArmor();
	// reduces armor
	void ReduceArmor();
	
	// gets armor
	const float GetArmor() const
	{
		return m_fArmor;
	}
private:
	
	// armor amount
	float m_fArmor;
	// initial armor value
	float m_fInitialArmor;
	// amount of armor that is added or subtracted
	// from armor
	const float m_fcArmorToken;
	// the max distance from the queen so that armor is
	// greater than zero
	const float m_fcMaxQueenDistance;
};

NiSmartPointer(ArmorAttribute);

#endif