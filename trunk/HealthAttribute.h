#ifndef HEALTHATTRIBUTE_H
#define HEALTHATTRIBUTE_H

#include "CharacterAttribute.h"

class GameCharacter;

class HealthAttribute : public CharacterAttribute
{
	NiDeclareRTTI;

public:

	// ctor / dtor
	HealthAttribute(GameCharacter* owner);
	~HealthAttribute();

	// updates the attribute
	void Update(float fTime);

	// resets health
	void Reset(float initialHealth);
	// increases health
	void IncreaseHealth(float value);
	// reduces health
	void ReduceHealth(float value);
	void ReduceHealth(float value, float modifier);
	
	// gets health
	const float GetHealth() const
	{
		return m_fHealth;
	}
private:
	
	// health amount
	float m_fHealth;
	// initial health value
	float m_fInitialHealth;

};

NiSmartPointer(HealthAttribute);

#endif