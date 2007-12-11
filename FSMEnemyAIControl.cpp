/**
* An enemy's FSM controller
*/
#include "FSMEnemyAIControl.h"
#include "Enemy.h"
#include "StateEnemyWander.h"
#include "StateLocustAttack.h"
#include "GameManager.h"
#include <NiTPointerList.h>
#include "Bee.h"
#include "HealerBee.h"
#include "Queen.h"
#include "Sound.h"

//-----------------------------------------------------------------------
NiImplementRTTI(FSMEnemyAIControl,FSMAIControl);
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
	// check in game objects for targets
	NxVec3 distance;
	float distanceMag;
	
	const NiTPointerList<GameObj3dPtr>& targets = m_pGameManager->GetObjects();
	if (targets.IsEmpty())
	{
		return 0;
	}

	NiTListIterator it = targets.GetHeadPos();
	for (int i=0; i<targets.GetSize(); i++)
	{
		GameObj3d* target = targets.Get(it);
		if (NiIsKindOf(Queen, target) || 
			NiIsKindOf(Bee, target) ||
			NiIsKindOf(HealerBee, target))
		{
			GameCharacter* current = (GameCharacter*)target;
			distance = current->GetActor()->getGlobalPosition() -
					   curPos;
			distanceMag = distance.magnitude();
			if (distanceMag < minDistance)
			{
				minDistance = distanceMag;
				closest = current;
			}			
		}				

		it = targets.GetNextPos(it);
	}

	return closest;

}
//----------------------------------------------------------------------
/**
*	Plays a sound when the owner is dying
*   
*/
void FSMEnemyAIControl::PlayDyingSound()
{
	SoundPtr snd = (Sound*)GetOwner()->GetAttribute(GameCharacter::ATTR_SOUND_1);
	if (snd)
	{
		snd->Play();
	}
}