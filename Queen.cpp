/**
 * Queen: The queen bee that the player controlls
 */

#include "Queen.h"
#include "FSMQueenAIControl.h"
#include "ResourceManager.h"

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
  m_bIssuedAttackEnemy(false),
  m_bIssuedTargetEnemy(false),
  m_bIssuedMoveForward(false),
  m_bIssuedMoveBackward(false),
  m_bIssuedMoveLeft(false),
  m_bIssuedMoveRight(false),
  m_bIssuedMoveVertical(false),
  m_bIssuedRotate(false),
  m_fRotateDx(0.0f),
  m_fRotateDy(0.0f)
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
 * Does extra updates
 * 
 * @param fTime
 */
void Queen::DoExtraUpdates(float fTime)
{
	// update the queen's controller
	FSMQueenAIControlPtr controller = (FSMQueenAIControl*)GetAttribute(GameCharacter::ATTR_CONTROLLER);
	NIASSERT(controller);
	controller->Update(fTime);
	
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

	// add a controller
	AddAttribute(GameCharacter::ATTR_CONTROLLER, NiNew FSMQueenAIControl(this));

	return true;
}
