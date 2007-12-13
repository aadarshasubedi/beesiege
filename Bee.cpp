/**
 * A queen's soldier.  
 */

#include "Bee.h"
#include "FSMBeeAIControl.h"
#include "Enemy.h"
#include "GameManager.h"
#include "HealthAttribute.h"
#include "ArmorAttribute.h"
#include "DamageAttribute.h"
#include "Sound.h"
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
	int a=1;
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
	m_fMaxHealth = ConfigurationManager::Get()->bee_initialHealth;
	health->Reset(m_fMaxHealth);
	AddAttribute(GameCharacter::ATTR_HEALTH, (CharacterAttribute*)health);
	// add an armor attribute
	AddAttribute(GameCharacter::ATTR_ARMOR, NiNew ArmorAttribute(this));
	// add a damage attribute
	DamageAttribute* dmg = NiNew DamageAttribute(this);
	dmg->Reset(ConfigurationManager::Get()->bee_damage);
	AddAttribute(GameCharacter::ATTR_DAMAGE, dmg);
	// add an FSMBeeAIControl
	AddAttribute(GameCharacter::ATTR_CONTROLLER, NiNew FSMBeeAIControl(this));
	// set initial position
	m_pActor->setGlobalPosition(GameManager::Get()->
		GetQueen()->GetActor()->getGlobalPosition() - NxVec3(50.0, 0.0, 0.0));

	SoundPtr sound = ResourceManager::Get()->GetSound(
		ResourceManager::RES_SOUND_BEE, this);
	if (sound)
	{
		AddAttribute(GameCharacter::ATTR_SOUND_DEFAULT, (CharacterAttribute*)sound);
		sound->Play();
	}

	AddAttribute(GameCharacter::ATTR_SOUND_1, (CharacterAttribute*) ResourceManager::Get()->GetSound(
		ResourceManager::RES_SOUND_BEE_AWAITING, this));

	AddAttribute(GameCharacter::ATTR_SOUND_2, (CharacterAttribute*) ResourceManager::Get()->GetSound(
		ResourceManager::RES_SOUND_BEE_DYING, this));

	// set dampings
	m_pActor->setLinearDamping(8.0f);
	m_pActor->setAngularDamping(8.0f);

	
	

	return true;
}