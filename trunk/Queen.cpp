/**
 * Queen: The queen bee that the player controlls
 */

#include "Queen.h"
#include "FSMQueenAIControl.h"
#include "ResourceManager.h"
#include "HealthAttribute.h"
#include "ConfigurationManager.h"
#include <NxScene.h>
//----------------------------------------------------------------------
// implements RTTI
NiImplementRTTI(Queen, GameCharacter);
//------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
Queen::Queen() 
: GameCharacter(ResourceManager::RES_MODEL_QUEEN),
  m_bIssuedSelectSoldiers(false),
  m_bIssuedSelectGatherers(false),
  m_bIssuedAttackEnemy(false),
  m_bIssuedGather(false),
  m_bIssuedTargetEnemy(false),
  m_bIssuedMoveForward(false),
  m_bIssuedMoveBackward(false),
  m_bIssuedMoveLeft(false),
  m_bIssuedMoveRight(false),
  m_bIssuedMoveVertical(false),
  m_bIssuedRotate(false),
  m_fRotateDx(0.0f),
  m_fRotateDy(0.0f),
  m_fHoney(200.0f)
{
	
}
//------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
Queen::~Queen()
{
	m_lSoldiers.RemoveAll();
	m_lHealers.RemoveAll();
	m_lGatherers.RemoveAll();
}
//------------------------------------------------------------------------ 
/**
* Adds a soldier to the list
* @param the soldier
*/
void Queen::AddSoldier(BeePtr soldier)
{
	m_lSoldiers.AddTail(soldier);
}
//------------------------------------------------------------------------ 
/**
* Removes a soldier from the list
* @param the soldier
*/
void Queen::RemoveSoldier(BeePtr soldier)
{
	m_lSoldiers.Remove(soldier);
}
//------------------------------------------------------------------------ 
/**
* Adds a healer to the list
* @param the healer
*/
void Queen::AddHealer(HealerBeePtr healer)
{
	m_lHealers.AddTail(healer);
}
//------------------------------------------------------------------------ 
/**
* Removes a healer from the list
* @param the healer
*/
void Queen::RemoveHealer(HealerBeePtr healer)
{
	m_lHealers.Remove(healer);
}
//------------------------------------------------------------------------ 
/**
* Adds a honey bee to the list
* @param the honey bee
*/
void Queen::AddGatherer(HoneyBeePtr gatherer)
{
	m_lGatherers.AddTail(gatherer);
}
//------------------------------------------------------------------------ 
/**
* Removes a honey bee from the list
* @param the honey bee
*/
void Queen::RemoveGatherer(HoneyBeePtr gatherer)
{
	m_lGatherers.Remove(gatherer);
}
//------------------------------------------------------------------------ 
/**
* Resets queen
*/
void Queen::Reset()
{
	m_lSoldiers.RemoveAll();
	m_lHealers.RemoveAll();
	m_lGatherers.RemoveAll();

	m_bIssuedSelectSoldiers = false;
	m_bIssuedSelectGatherers = false;
	m_bIssuedAttackEnemy = false;
	m_bIssuedGather = false;
	m_bIssuedTargetEnemy = false;
	m_bIssuedMoveForward = false;
	m_bIssuedMoveBackward = false;
	m_bIssuedMoveLeft = false;
	m_bIssuedMoveRight = false;
	m_bIssuedMoveVertical = false;
	m_bIssuedRotate = false;
	
	m_fHoney = 200.0f;

	HealthAttribute* health = (HealthAttribute*)GetAttribute(GameCharacter::ATTR_HEALTH);
	if (health)
	{
		health->Reset(m_fMaxHealth);
	}

	m_tAttributes.RemoveAt(GameCharacter::ATTR_CONTROLLER);
	// add a controller
	AddAttribute(GameCharacter::ATTR_CONTROLLER, NiNew FSMQueenAIControl(this));
}
//------------------------------------------------------------------------ 
/** 
 * Does extra updates
 * 
 * @param fTime
 */
void Queen::DoExtraUpdates(float fTime)
{
	GameCharacter::DoExtraUpdates(fTime);
}
//------------------------------------------------------------------------ 
/** 
 * Does extra initializations
 * 
 * 
 * @return bool
 */
bool Queen::DoExtraInits()
{
	if (!GameCharacter::DoExtraInits())
	{
		return false;
	}

	// add a health attribute
	HealthAttributePtr health = NiNew HealthAttribute(this);
	m_fMaxHealth = ConfigurationManager::Get()->queen_initialHealth;
	health->Reset(m_fMaxHealth);
	AddAttribute(GameCharacter::ATTR_HEALTH, (CharacterAttribute*)health);
	// add a controller
	AddAttribute(GameCharacter::ATTR_CONTROLLER, NiNew FSMQueenAIControl(this));

	return true;
}
