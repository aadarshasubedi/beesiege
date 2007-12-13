/**
 * A bee that heals allies and dies after
 * she's done
 */

#include "HoneyBee.h"
#include "HealthAttribute.h"
#include "ArmorAttribute.h"
#include "Sound.h"
#include "Queen.h"
#include "ConfigurationManager.h"
#include "FSMHoneyBeeAIControl.h"
#include "GameManager.h"
//----------------------------------------------------------------------
// implements RTTI
NiImplementRTTI(HoneyBee, GameCharacter);
//------------------------------------------------------------------------
/** 
 * Ctor
 * 
 */
HoneyBee::HoneyBee() : GameCharacter(ResourceManager::RES_MODEL_HONEYBEE),
					   m_bIsGatherIssued(false),
					   m_pTargetFlower(0),
					   m_fHoneyGathered(0.0f),
					   m_pGameManager(GameManager::Get())
{
}
//------------------------------------------------------------------------
/** 
 * Dtor
 * 
 */
HoneyBee::~HoneyBee()
{
	
}
//------------------------------------------------------------------------
/** 
 * Updates the bee
 * 
 * @param fTime
 */
void HoneyBee::DoExtraUpdates(float fTime)
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
bool HoneyBee::DoExtraInits()
{
	if (!GameCharacter::DoExtraInits())
	{
		return false;
	}

	// add a health attribute
	HealthAttributePtr health = NiNew HealthAttribute(this);
	m_fMaxHealth = ConfigurationManager::Get()->honeyBee_initialHealth;
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

	// add an FSMHoneyBeeAIControl
	AddAttribute(GameCharacter::ATTR_CONTROLLER, NiNew FSMHoneyBeeAIControl(this));

	// set dampings
	m_pActor->setLinearDamping(8.0f);
	m_pActor->setAngularDamping(8.0f);

	return true;
}
//------------------------------------------------------------------------
/** 
 * Give gathered honey to queen
 * 
 */
void HoneyBee::GiveHoneyToQueen()
{
	if (!HasHoney())
	{
		return;
	}

	NiPoint3 pos = m_spNode->GetTranslate();
	Queen* queen = m_pGameManager->GetQueen();
	NxVec3 queenPos = queen->GetActor()->getGlobalPosition();

	NxVec3 distance = NxVec3(pos.x, pos.y, pos.z) - queenPos;
	if (distance.magnitude() <= 100.0f)
	{
		queen->IncreaseHoney(m_fHoneyGathered);
		m_fHoneyGathered = 0.0f;
	}
					  
}