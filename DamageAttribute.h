#ifndef DAMAGEATTRIBUTE_H
#define DAMAGEATTRIBUTE_H

#include "CharacterAttribute.h"

class GameCharacter;

class DamageAttribute : public CharacterAttribute
{
	NiDeclareRTTI;
public:

	// ctor / dtor
	DamageAttribute(GameCharacter* owner);
	~DamageAttribute();

	// updates the attribute
	void Update(float fTime);

	// resets damage to specified value
	void Reset(float value)
	{
		m_fInitialDamage = value;
		m_fDamage = value;
	}

	// gets armor
	const float GetDamage() const
	{
		return m_fDamage;
	}
private:
	
	// damage amount
	float m_fDamage;
	// initial damage
    float m_fInitialDamage;
	// the max distance from the queen so that damage is
	// greater than default
	const float m_fcMaxQueenDistance;
};

NiSmartPointer(DamageAttribute);

#endif