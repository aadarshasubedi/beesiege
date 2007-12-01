/**
*	A character's health attribute
*/

#include "HealthAttribute.h"
#include "ArmorAttribute.h"
#include "GameCharacter.h"
//-------------------------------------------------------------------------
/**
* Ctor
*/
HealthAttribute::HealthAttribute(GameCharacter *owner)
: CharacterAttribute(owner), m_fInitialHealth(0.0f), m_fHealth(0.0f), m_fcHealthToken(1.0f)
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
void HealthAttribute::ReduceHealth()
{
	if (m_fHealth > 0.0f)
	{
		// health decrease depends on armor
		ArmorAttribute* armor = (ArmorAttribute*)GetOwner()->GetAttribute(GameCharacter::ATTR_ARMOR);
		if (armor)
		{
			float armorValue = armor->GetArmor();
			m_fHealth -= armorValue > 0.0f ? m_fcHealthToken / armorValue : m_fcHealthToken;
		}
		else
		{
			m_fHealth -= m_fcHealthToken;
		}
			
	}
}
//-------------------------------------------------------------------------
/**
* Reduce Health by a modifier * healthToken
* @param modifier
*/
void HealthAttribute::ReduceHealth(float modifier)
{
	if (m_fHealth > 0.0f)
	{
		m_fHealth -= m_fcHealthToken * modifier;	
	}
}
//-------------------------------------------------------------------------
/**
* Increase Health by a constant factor
*/
void HealthAttribute::IncreaseHealth()
{
	m_fHealth += m_fcHealthToken;
	if (m_fHealth > m_fInitialHealth)
	{
		m_fHealth = m_fInitialHealth;
	}
}