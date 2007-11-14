#ifndef HEALTHATTRIBUTE_H
#define HEALTHATTRIBUTE_H

#include "CharacterAttribute.h"

class GameCharacter;

class HealthAttribute : public CharacterAttribute
{
public:

	HealthAttribute(GameCharacter* owner);
	~HealthAttribute();

	void Update(float fTime);

	void Reset(float initialHealth);
	void IncreaseHealth();
	void ReduceHealth();

	const float GetHealth() const
	{
		return m_fHealth;
	}
private:

	float m_fHealth;
	float m_fInitialHealth;
	const float m_fcHealthToken;
};

NiSmartPointer(HealthAttribute);

#endif