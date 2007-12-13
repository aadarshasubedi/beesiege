/**
 * A bee that heals allies and dies after
 * she's done
 */

#include "HealerBee.h"
#include "HealthAttribute.h"
#include "ArmorAttribute.h"
#include "Sound.h"
#include "ConfigurationManager.h"
#include "FSMHealerAIControl.h"
#include "GameManager.h"
//----------------------------------------------------------------------
// implements RTTI
NiImplementRTTI(HealerBee, GameCharacter);
//------------------------------------------------------------------------
/** 
 * Ctor
 * 
 */
HealerBee::HealerBee() : GameCharacter(ResourceManager::RES_MODEL_HEALERBEE)
{
}
//------------------------------------------------------------------------
/** 
 * Dtor
 * 
 */
HealerBee::~HealerBee()
{
	
}
//------------------------------------------------------------------------
/** 
 * Updates the bee
 * 
 * @param fTime
 */
void HealerBee::DoExtraUpdates(float fTime)
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
bool HealerBee::DoExtraInits()
{
	if (!GameCharacter::DoExtraInits())
	{
		return false;
	}

	// add a health attribute
	HealthAttributePtr health = NiNew HealthAttribute(this);
	m_fMaxHealth = ConfigurationManager::Get()->healer_initialHealth;
	health->Reset(m_fMaxHealth);
	AddAttribute(GameCharacter::ATTR_HEALTH, (CharacterAttribute*)health);
	// add an armor attribute
	AddAttribute(GameCharacter::ATTR_ARMOR, NiNew ArmorAttribute(this));
	
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

	// add an FSMBeeAIControl
	AddAttribute(GameCharacter::ATTR_CONTROLLER, NiNew FSMHealerAIControl(this));

	// set dampings
	m_pActor->setLinearDamping(8.0f);
	m_pActor->setAngularDamping(8.0f);

	return true;
}