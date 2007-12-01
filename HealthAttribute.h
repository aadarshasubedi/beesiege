#ifndef HEALTHATTRIBUTE_H
#define HEALTHATTRIBUTE_H

#include "CharacterAttribute.h"

class GameCharacter;

class HealthAttribute : public CharacterAttribute
{
public:

	// ctor / dtor
	HealthAttribute(GameCharacter* owner);
	~HealthAttribute();

	// updates the attribute
	void Update(float fTime);

	// resets health
	void Reset(float initialHealth);
	// increases health
	void IncreaseHealth();
	// reduces health
	void ReduceHealth();
	void ReduceHealth(float modifier);
	
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
	// amount of health that is added or subtracted
	// from health
	const float m_fcHealthToken;
};

NiSmartPointer(HealthAttribute);

#endif