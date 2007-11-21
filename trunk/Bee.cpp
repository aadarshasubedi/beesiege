/**
 * A Bee or a queen's soldier. 
 */

#include "Bee.h"
#include "FSMBeeAIControl.h"
#include "Enemy.h"
#include "GameManager.h"
#include "HealthAttribute.h"
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
			 m_bIssuedAttackCommand(false)
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
	FSMBeeAIControl* controller = (FSMBeeAIControl*)GetAttribute(GameCharacter::ATTR_CONTROLLER);
	if (controller)
	{
		controller->Update(fTime);	
	}
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

	// add an FSMBeeAIControl
	AddAttribute(GameCharacter::ATTR_CONTROLLER, NiNew FSMBeeAIControl(this));
	// add a health attribute
	HealthAttributePtr health = NiNew HealthAttribute(this);
	health->Reset(10.0f);
	AddAttribute(GameCharacter::ATTR_HEALTH, (CharacterAttribute*)health);
	// set initial position
	m_pActor->setGlobalPosition(GameManager::Get()->
		GetQueen()->GetActor()->getGlobalPosition() - NxVec3(50.0, 0.0, 0.0));

	// set dampings
	m_pActor->setLinearDamping(10.0f);
	m_pActor->setAngularDamping(10.0f);
	return true;
}