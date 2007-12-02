/**
*	A character's armor attribute
*/

#include "ArmorAttribute.h"
#include "HealthAttribute.h"
#include "GameManager.h"
#include "Queen.h"
#include "GameCharacter.h"
#include "ConfigurationManager.h"
//-------------------------------------------------------------------------
/**
* Ctor
*/
ArmorAttribute::ArmorAttribute(GameCharacter *owner)
: CharacterAttribute(owner), m_fArmor(0.0f),
m_fcMaxQueenDistance(ConfigurationManager::Get()->bee_armorEffectiveDistance)
{
}
//-------------------------------------------------------------------------
/**
* Dtor
*/
ArmorAttribute::~ArmorAttribute()
{
}
//-------------------------------------------------------------------------
/**
* Armor increases / decreases depending on the distance
* of the owner from the queen 
* @param delta time
*/
void ArmorAttribute::Update(float fTime)
{
	NxVec3 queenPos = GameManager::Get()->GetQueen()->GetActor()->getGlobalPosition();
	NxVec3 ownerPos = GetOwner()->GetActor()->getGlobalPosition();
	float distance = NxVec3(queenPos - ownerPos).magnitude();
	m_fArmor = m_fcMaxQueenDistance - distance;

	// if armor is negative then reduce health
	if (m_fArmor < 0.0f)
	{
		HealthAttribute* health = (HealthAttribute*)GetOwner()->GetAttribute(GameCharacter::ATTR_HEALTH);
		if (health)
		{
			health->ReduceHealth(1.0f, -m_fArmor * 0.01f);
		}
	}
}