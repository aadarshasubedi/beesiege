/**
*	A character's armor attribute
*/

#include "ArmorAttribute.h"
#include "HealthAttribute.h"
#include "GameManager.h"
#include "Queen.h"
#include "GameCharacter.h"
#include "ConfigurationManager.h"


//---------------------------------------------------------------------------------
NiImplementRTTI(ArmorAttribute,CharacterAttribute);
//-------------------------------------------------------------------------
/**
* Ctor
*/
ArmorAttribute::ArmorAttribute(GameCharacter *owner)
: CharacterAttribute(owner), m_fArmor(0.0f),
m_fcMaxQueenDistance(ConfigurationManager::Get()->bee_armorEffectiveDistance),
m_fcArmorCoefficient(ConfigurationManager::Get()->bee_armorCoefficient)
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
    if (distance < 1.0f)
	{
		distance = 1.0f;
	}

	m_fArmor = distance < m_fcMaxQueenDistance ? 
		(m_fcMaxQueenDistance / distance) * m_fcArmorCoefficient :
		0.0f;
	

}