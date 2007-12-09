/**
*	A controller that uses an FSM to control a queen
*/
#include "FSMQueenAIControl.h"
#include "GameManager.h"
#include "Queen.h"
#include "StateQueenTargetEnemy.h"
#include "StateQueenSelectSoldiers.h"
#include "ConfigurationManager.h"
#include "Flower.h"
//--------------------------------------------------------------------
/**
* Ctor
* @param the queen to be controlled
*/
FSMQueenAIControl::FSMQueenAIControl(Queen* queen) 
: FSMAIControl((GameCharacter*)queen),
  issuedTargetEnemyCommand(false),
  issuedSelectSoldiersCommand(false),
  issuedAttackCommand(false),
  issuedMoveForwardCommand(false),
  issuedMoveBackwardCommand(false),
  issuedMoveLeftCommand(false),
  issuedMoveRightCommand(false),
  issuedMoveVerticalCommand(false),
  issuedRotateCommand(false),
  m_pCurrentFlowerTarget(0),
  m_iFrames(0),
  m_pConfigManager(ConfigurationManager::Get()),
  m_fcFlowersRadius(600.0f)
{
	StateQueenTargetEnemy* defaultState = NiNew StateQueenTargetEnemy(this);
	m_spMachine->AddState(defaultState, FSM_QUEEN_TARGETENEMY);
	m_spMachine->AddState(NiNew StateQueenSelectSoldiers(this), FSM_QUEEN_SELECTSOLDIERS);
	m_spMachine->SetDefaultState(defaultState);
}
//--------------------------------------------------------------------
/*
* Dtor
*/
FSMQueenAIControl::~FSMQueenAIControl()
{
}
//-----------------------------------------------------------------------
/**
* Updates the required variables that the controller needs to function
* @param delta time
*/
void FSMQueenAIControl::UpdatePerceptions(float fTime)
{
	NIASSERT(m_pOwner);
	QueenPtr queenOwner = (Queen*)m_pOwner;
	issuedSelectSoldiersCommand = queenOwner->WasSelectSoldiersIssued();
	issuedAttackCommand         = queenOwner->WasAttackEnemyIssued();
	issuedTargetEnemyCommand    = queenOwner->WasTargetEnemyIssued();
	issuedMoveForwardCommand	= queenOwner->WasMoveForwardIssued();
	issuedMoveBackwardCommand	= queenOwner->WasMoveBackwardIssued();
	issuedMoveLeftCommand		= queenOwner->WasMoveLeftIssued();
	issuedMoveRightCommand		= queenOwner->WasMoveRightIssued();
	issuedMoveVerticalCommand	= queenOwner->WasMoveVerticalIssued();
	issuedRotateCommand			= queenOwner->WasRotateIssued();

	queenOwner->SetMoveBackward(false);
	queenOwner->SetMoveForward(false);
	queenOwner->SetMoveLeft(false);
	queenOwner->SetMoveRight(false);
	queenOwner->SetAttackEnemy(false);
	queenOwner->SetTargetEnemy(false);
	queenOwner->SetSelectSoldiers(false);
}
//-----------------------------------------------------------------------
/**
* Performs extra updates if necessary
* @param delta time
*/
void FSMQueenAIControl::DoExtraUpdates(float fTime)
{
	if (issuedMoveForwardCommand)
	{
		issuedMoveForwardCommand = false;
		MoveQueenForward();
	}
	else if (issuedMoveBackwardCommand)
	{
		issuedMoveBackwardCommand = false;
		MoveQueenBackward();
	}

	if (issuedMoveLeftCommand)
	{
		issuedMoveLeftCommand = false;
		MoveQueenLeft();
	}
	else if (issuedMoveRightCommand)
	{
		issuedMoveRightCommand = false;
		MoveQueenRight();
	}

	if (issuedMoveVerticalCommand)
	{
		issuedMoveVerticalCommand = false;
		MoveQueenVertical();
	}

	if (issuedRotateCommand)
	{
		issuedRotateCommand = false;
		RotateQueen();
	}	

	m_iFrames--;
	if (m_iFrames <= 0)
	{
		m_iFrames = 5;
		TargetClosestFlowers();
	}
}
//------------------------------------------------------------------------ 
/** 
 * Adds a forward force
 * 
 */
void FSMQueenAIControl::MoveQueenForward()
{
	GetAgent()->GetActor()->addLocalForce(
		NxVec3(m_pConfigManager->queen_speedGain, 0.0, 0.0));
}
//------------------------------------------------------------------------
/** 
 * Adds a backward force
 * 
 */
void FSMQueenAIControl::MoveQueenBackward()
{
	GetAgent()->GetActor()->addLocalForce(
		NxVec3(-m_pConfigManager->queen_speedGain, 0.0, 0.0));
}
//------------------------------------------------------------------------
/** 
 * Adds a left force
 * 
 */
void FSMQueenAIControl::MoveQueenLeft()
{
	GetAgent()->GetActor()->addLocalForce(
		NxVec3(0.0, 0.0, -m_pConfigManager->queen_speedGain));
	
}
//------------------------------------------------------------------------
/** 
 * Adds a right force
 * 
 */
void FSMQueenAIControl::MoveQueenRight()
{
	GetAgent()->GetActor()->addLocalForce(
		NxVec3(0.0, 0.0, m_pConfigManager->queen_speedGain));	
}
//------------------------------------------------------------------------
/** 
 * Adds a vertical force
 * 
 */
void FSMQueenAIControl::MoveQueenVertical()
{
	float moveUpSpeedGain = m_pConfigManager->queen_moveUpSpeedGain;
	float dy = ((Queen*)GetOwner())->GetRotateDy();
	GetAgent()->GetActor()->addLocalForce(NxVec3(0.0, -dy*moveUpSpeedGain, 0.0));	
}
//------------------------------------------------------------------------ 
/** 
 * Adds a torque 
 * 
 */
void FSMQueenAIControl::RotateQueen()
{
	float rotationGain = m_pConfigManager->queen_rotationGain;
	float dx = ((Queen*)GetOwner())->GetRotateDx();
	GetAgent()->GetActor()->addLocalTorque(NxVec3(0.0, -dx*rotationGain,0.0));

	NxMat33 rotation = GetAgent()->GetActor()->getGlobalOrientation();
	rotation.setColumn(1, NxVec3(0.0, 1.0, 0.0));
	GetAgent()->GetActor()->setGlobalOrientation(rotation);
}
//------------------------------------------------------------------------ 
/** 
 * Targets the closest flower bed 
 * 
 */
void FSMQueenAIControl::TargetClosestFlowers()
{
	// if empty return
	const NiTPointerList<FlowerPtr>& flowers = m_pGameManager->GetFlowers();
	if (flowers.IsEmpty()) return;

	NxVec3 pos = GetAgent()->GetActor()->getGlobalPosition();
	NxVec3 distance;
	
	// if we have a target and it is in the radius just
	// use this one for better performance
	if (m_pCurrentFlowerTarget)
	{
		NiPoint3 targetPos = m_pCurrentFlowerTarget->GetNode()->GetTranslate();
		distance = NxVec3(targetPos.x, targetPos.y, targetPos.z) - pos;
		if (distance.magnitude() < m_fcFlowersRadius)
			return;

		// current target is not in radius so deselect it
		m_pCurrentFlowerTarget->SetEmmitance(NiColor(0.0, 0.0, 0.0));
	}

	// find min distance
	float minDistance = 50000.0f;
	NiTListIterator it = flowers.GetHeadPos();
	FlowerPtr current = 0;
	for (int i=0; i<flowers.GetSize(); i++)
	{
		current = flowers.Get(it);
		// if this is our current target continue
		// since we already checked that
		if (current == m_pCurrentFlowerTarget) 
			continue;

		NiPoint3 flowerPos = current->GetNode()->GetTranslate();
		distance = NxVec3(flowerPos.x, flowerPos.y, flowerPos.z) - pos;
		float distanceMag = distance.magnitude();
		if (distanceMag < m_fcFlowersRadius)
		{
			if (distanceMag < minDistance)
			{
				minDistance = distanceMag;
				m_pCurrentFlowerTarget = current;
			}
		}

		it = flowers.GetNextPos(it);
	}

	if (m_pCurrentFlowerTarget)
	{
		m_pCurrentFlowerTarget->SetEmmitance(NiColor(0.0, 0.5, 1.0));
	}
}