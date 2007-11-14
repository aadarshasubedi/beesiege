/**
* An enemy's FSM controller
*/
#include "FSMEnemyAIControl.h"
#include "Enemy.h"
#include "StateEnemyWander.h"
//-----------------------------------------------------------------------
/**
* Ctor
* @param The enemy that needs to be controlled
*/
FSMEnemyAIControl::FSMEnemyAIControl(Enemy* enemy) : FSMAIControl((GameCharacter*)enemy)
{
	StateEnemyWander* defaultState = NiNew StateEnemyWander(this);
	m_spMachine->AddState(defaultState, FSM_ENEMY_WANDER);
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