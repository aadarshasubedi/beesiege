/**
*	A character's health attribute
*/

#include "HealthAttribute.h"

//-------------------------------------------------------------------------
/**
* Ctor
*/
HealthAttribute::HealthAttribute(GameCharacter *owner)
: CharacterAttribute(owner), m_fInitialHealth(0.0f), m_fHealth(0.0f), m_fcHealthToken(10.0f)
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
* Reduce Health by a constant factor
*/
void HealthAttribute::ReduceHealth()
{
	if (m_fHealth > 0.0f)
		m_fHealth -= m_fcHealthToken;
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