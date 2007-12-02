/**
* An enemy's FSM controller
*/
#include "FSMEnemyAIControl.h"
#include "Enemy.h"
#include "StateEnemyWander.h"
#include "StateLocustAttack.h"
#include "GameManager.h"
#include <NiTPointerList.h>
//-----------------------------------------------------------------------
/**
* Ctor
* @param The enemy that needs to be controlled
*/
FSMEnemyAIControl::FSMEnemyAIControl(Enemy* enemy) : FSMAIControl((GameCharacter*)enemy)
{
	StateEnemyWander* defaultState = NiNew StateEnemyWander(this);
	m_spMachine->AddState(defaultState, FSM_ENEMY_WANDER);
	m_spMachine->AddState(NiNew StateLocustAttack(this), FSM_ENEMY_LOCUST_ATTACK);
	m_spMachine->SetDefaultState(defaultState);
}
//-----------------------------------------------------------------------
/**
* Dtor
* 
*/
FSMEnemyAIControl::~FSMEnemyAIControl()
{

}
//-----------------------------------------------------------------------
/**
* Updates the required variables that the controller needs to function
* @param delta time
*/
void FSMEnemyAIControl::UpdatePerceptions(float fTime)
{
	
}
//-----------------------------------------------------------------------
/**
* Performs extra updates if necessary
* @param delta time
*/
void FSMEnemyAIControl::DoExtraUpdates(float fTime)
{
		
}
//-----------------------------------------------------------------------
/**
* Searches for targets in a radius
* @param delta time
*/
GameCharacter* FSMEnemyAIControl::IsTargetAtProximity(float radius)
{
	float minDistance = radius + 1.0f;
	GameCharacter* closest = 0;
	// find min distance
	NxVec3 curPos = GetOwner()->GetActor()->getGlobalPosition();
	// first check queen
	NxVec3 distance = GameManager::Get()->GetQueen()->
		GetActor()->getGlobalPosition() - curPos;
	float distanceMag = distance.magnitude();
	if (distanceMag < minDistance)
	{
		minDistance = distanceMag;
		closest = (GameCharacter*)GameManager::Get()->GetQueen();
	}
	
	// then check soldiers
	const NiTPointerList<BeePtr>& soldiers = 
		GameManager::Get()->GetQueen()->GetSoldiers();
	if (soldiers.IsEmpty())
	{
		return closest;
	}

	NiTListIterator it = soldiers.GetHeadPos();
	for (int i=0; i<soldiers.GetSize(); i++)
	{
		GameCharacter* current = (GameCharacter*)soldiers.Get(it);
		distance = current->GetActor()->getGlobalPosition() -
			curPos;
		distanceMag = distance.magnitude();
		if (distanceMag < minDistance)
		{
			minDistance = distanceMag;
			closest = current;
		}
		it = soldiers.GetNextPos(it);
	}

	return closest;

}