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
	FSMQueenAIControlPtr controller = (FSMQueenAIControl*)GetAttribute(GameCharacter::ATTR_CONTROLLER);
	NIASSERT(controller);
	controller->Update(fTime);
	/*
	// make queen parallel to the XZ plane
	NxMat33 rotation = m_spAgent->GetActor()->getGlobalOrientation();
	rotation.setColumn(1, NxVec3(0.0, 1.0, 0.0));
	m_spAgent->GetActor()->setGlobalOrientation(rotation);

	// if the current target move out of the queen's radius then
	// stop targeting it
	if (m_spCurrentTarget)
	{
		NxVec3 distance = m_spCurrentTarget->GetAgent()->GetActor()->getGlobalPosition() - 
			m_spAgent->GetActor()->getGlobalPosition();
		if (distance.magnitude() > m_fcQueenViewRadius)
		{
			m_spCurrentTarget->SetEmmitance(NiColor(0.0, 0.0, 0.0));
			m_spCurrentTarget = 0;
		}
	}

	// if queen goes too high then increse fog significantly so 
	// the player cannot see anything. This will make him want to 
	// go back to a normal height where we want him.
	NiFogProperty* fog = (NiFogProperty*)GameManager::Get()->GetGameApp()->
			GetScene()->GetProperty(NiProperty::FOG);
	if (fog)
	{
		float y = m_spAgent->GetActor()->getGlobalPosition().y; 
		if ( y >= m_fcMaxHeight)
		{
			fog->SetDepth(y*y*y/m_fcFogScaleValue);	
		}
		else
		{
			fog->SetDepth(m_fcFogDefaultDepth);
		}
	}
	*/
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

	AddAttribute(GameCharacter::ATTR_CONTROLLER, NiNew FSMQueenAIControl(this));

	return true;
}
