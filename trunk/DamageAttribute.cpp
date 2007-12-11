/**
*	A character's Damage attribute
*/

#include "DamageAttribute.h"
#include "GameManager.h"
#include "Queen.h"
#include "GameCharacter.h"
#include "ConfigurationManager.h"


//-------------------------------------------------------------------------
NiImplementRTTI(DamageAttribute,CharacterAttribute);
//-------------------------------------------------------------------------
/**
* Ctor
*/
DamageAttribute::DamageAttribute(GameCharacter *owner)
: CharacterAttribute(owner), 
m_fcMaxQueenDistance(ConfigurationManager::Get()->bee_damageEffectiveDistance), 
m_fDamage(1.0f), m_fInitialDamage(1.0f)
{
}
//-------------------------------------------------------------------------
/**
* Dtor
*/
DamageAttribute::~DamageAttribute()
{
}
//-------------------------------------------------------------------------
/**
* Damage increases / decreases depending on the distance
* of the owner from the queen 
* @param delta time
*/
void DamageAttribute::Update(float fTime)
{
	NxVec3 queenPos = GameManager::Get()->GetQueen()->GetActor()->getGlobalPosition();
	NxVec3 ownerPos = GetOwner()->GetActor()->getGlobalPosition();
	float distance = NxVec3(queenPos - ownerPos).magnitude();

	// if owner is close to queen then increase damage
	if (distance <= m_fcMaxQueenDistance)
	{
		// max damage = 10
		if (distance <= m_fcMaxQueenDistance * 0.1f)
		{
			m_fDamage = 10.0f;
		}
		else
		{
			m_fDamage = m_fcMaxQueenDistance / distance;
		}		
	}
	else
	{
		m_fDamage = m_fInitialDamage;
	}
}