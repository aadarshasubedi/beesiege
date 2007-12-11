/**
*	A character's health attribute
*/

#include "HealthAttribute.h"
#include "ArmorAttribute.h"
#include "GameCharacter.h"


//-------------------------------------------------------------------------
NiImplementRTTI(HealthAttribute,CharacterAttribute);
//-------------------------------------------------------------------------
/**
* Ctor
*/
HealthAttribute::HealthAttribute(GameCharacter *owner)
: CharacterAttribute(owner), m_fInitialHealth(0.0f), m_fHealth(0.0f)
{
}
//-------------------------------------------------------------------------
/**
* Dtor
*/
HealthAttribute::~HealthAttribute()
{
}
//-------------------------------------------------------------------------
/**
* Updates the attribute if necessary
* @param delta time
*/
void HealthAttribute::Update(float fTime)
{
	
}
//-------------------------------------------------------------------------
/**
* Reset health to an initial value
* @param initialHealth
*/
void HealthAttribute::Reset(float initialHealth)
{
	m_fInitialHealth = initialHealth;
	m_fHealth = initialHealth;
}
//-------------------------------------------------------------------------
/**
* Reduce Health 
*/
void HealthAttribute::ReduceHealth(float value)
{
	if (m_fHealth > 0.0f)
	{
		// health decrease depends on armor
		ArmorAttribute* armor = (ArmorAttribute*)GetOwner()->GetAttribute(GameCharacter::ATTR_ARMOR);
		if (armor)
		{
			float armorValue = armor->GetArmor();
			m_fHealth -= armorValue > 0.0f ? value / armorValue : value;
		}
		else
		{
			m_fHealth -= value;
		}
			
	}
}
//-------------------------------------------------------------------------
/**
* Reduce Health by a modifier * healthToken
* @param modifier
*/
void HealthAttribute::ReduceHealth(float value, float modifier)
{
	if (m_fHealth > 0.0f)
	{
		m_fHealth -= value * modifier;	
	}
}
//-------------------------------------------------------------------------
/**
* Increase Health 
*/
void HealthAttribute::IncreaseHealth(float value)
{
	m_fHealth += value;
	if (m_fHealth > m_fInitialHealth)
	{
		m_fHealth = m_fInitialHealth;
	}
}