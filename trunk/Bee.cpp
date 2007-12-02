/**
 * A Bee or a queen's soldier. 
 */

#include "Bee.h"
#include "FSMBeeAIControl.h"
#include "Enemy.h"
#include "GameManager.h"
#include "HealthAttribute.h"
#include "ArmorAttribute.h"
#include "DamageAttribute.h"
#include "ConfigurationManager.h"
#include "NiTMap.h"

//----------------------------------------------------------------------
// implements RTTI
NiImplementRTTI(Bee, GameCharacter);
//------------------------------------------------------------------------
/** 
 * Ctor
 * 
 */
Bee::Bee() : GameCharacter(ResourceManager::RES_MODEL_BEE),
			 m_pEnemyTarget(0),
			 m_bIssuedAttackCommand(false),
			 m_bHighlighted(false)
{
}
//------------------------------------------------------------------------
/** 
 * Dtor
 * 
 */
Bee::~Bee()
{
	
}
//------------------------------------------------------------------------
/** 
 * Updates the bee
 * 
 * @param fTime
 */
void Bee::DoExtraUpdates(float fTime)
{
	GameCharacter::DoExtraUpdates(fTime);
	
}
//------------------------------------------------------------------------ 
/** 
 * Initializes the bee's attributes 
 * 
 * 
 * @return bool
 */
bool Bee::DoExtraInits()
{
	if (!GameCharacter::DoExtraInits())
	{
		return false;
	}

	// add a health attribute
	HealthAttributePtr health = NiNew HealthAttribute(this);
	health->Reset(ConfigurationManager::Get()->bee_initialHealth);
	AddAttribute(GameCharacter::ATTR_HEALTH, (CharacterAttribute*)health);
	// add an armor attribute
	AddAttribute(GameCharacter::ATTR_ARMOR, NiNew ArmorAttribute(this));
	// add a damage attribute
	AddAttribute(GameCharacter::ATTR_DAMAGE, NiNew DamageAttribute(this));
	// add an FSMBeeAIControl
	AddAttribute(GameCharacter::ATTR_CONTROLLER, NiNew FSMBeeAIControl(this));
	// set initial position
	m_pActor->setGlobalPosition(GameManager::Get()->
		GetQueen()->GetActor()->getGlobalPosition() - NxVec3(50.0, 0.0, 0.0));

	// set dampings
	m_pActor->setLinearDamping(10.0f);
	m_pActor->setAngularDamping(10.0f);

	
	

	return true;
}