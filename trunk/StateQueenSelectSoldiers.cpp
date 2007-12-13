/**
*	A state that allows the queen to select soldiers
*/
#include "StateQueenSelectSoldiers.h"
#include "Queen.h"
#include "FSMMachine.h"
#include "GameManager.h"
#include "FSMQueenAIControl.h"
#include "ConfigurationManager.h"
#include "HealthAttribute.h"
#include "Sound.h"
#include <NiPhysX.h>

//----------------------------------------------------------------------
/**
*	Ctor
*/
StateQueenSelectSoldiers::StateQueenSelectSoldiers(FSMAIControl* control, 
												   int type)
: FSMState(control, type), m_pTarget(0), m_pTargetHealth(0)
{
}

//----------------------------------------------------------------------
/**
*	Dtor
*/
StateQueenSelectSoldiers::~StateQueenSelectSoldiers()
{
	m_lSelectedSoldiers.RemoveAll();
}
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is entered
*/
void StateQueenSelectSoldiers::Enter()
{
	m_fSelectionTimer = ConfigurationManager::Get()->timer_selectSoldiers;
	m_pTarget = GameManager::Get()->GetCurrentTarget();
	if (m_pTarget)
	{
		m_pTargetHealth = (HealthAttribute*)m_pTarget->
		GetAttribute(GameCharacter::ATTR_HEALTH);
	}
}
//----------------------------------------------------------------------
/**
*	Updates the state
*   @param delta time
*/
void StateQueenSelectSoldiers::Update(float fTime)
{
	IsOwnerDead();

	FSMQueenAIControl* controller = (FSMQueenAIControl*)m_control;
	NIASSERT(controller);

	if (controller->issuedSelectSoldiersCommand)
	{
		controller->issuedSelectSoldiersCommand = false;
		SelectMoreSoldiers();
	}

}
//----------------------------------------------------------------------
/**
*	Checks for transition conditions
*   @param delta time
*/
FSMState* StateQueenSelectSoldiers::CheckTransitions(float fTime)
{
	FSMQueenAIControl* controller = (FSMQueenAIControl*)m_control;
	NIASSERT(controller);
	FSMState* nextState = controller->GetMachine()->GetCurrentState();;
	
	if (controller->issuedAttackCommand ||
		!m_pTarget)
	{
		nextState = controller->GetMachine()->GetState(FSM_QUEEN_TARGETENEMY);
		NIASSERT(nextState);
	}
	return nextState;
}
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is exited
*   
*/
void StateQueenSelectSoldiers::Exit()
{
	// command selected soldiers to attack
	if (!m_lSelectedSoldiers.IsEmpty() && m_pTarget)
	{
		NiTListIterator it = m_lSelectedSoldiers.GetHeadPos();
		for (int i=0; i<m_lSelectedSoldiers.GetSize(); i++)
		{
			m_lSelectedSoldiers.Get(it)->SetAttack(m_pTarget);
			it = m_lSelectedSoldiers.GetNextPos(it);
		}
	}
	m_pTarget = 0;
	m_pTargetHealth = 0;
	m_lSelectedSoldiers.RemoveAll();
}
//------------------------------------------------------------------------ 
/** 
 * Targets next closest enemy
 * 
 */
void StateQueenSelectSoldiers::SelectMoreSoldiers()
{
	// get the target's position
	NxVec3 target;
	if (m_pTarget)
	{
		if (m_pTargetHealth)
		{
			if (m_pTargetHealth->GetHealth() <= 0.0f)
			{
				m_pTarget = 0;
				m_pTargetHealth = 0;
				m_fSelectionTimer = 0.0f;
				return;
			}
			else
			{
				m_fSelectionTimer += GameManager::Get()->GetDeltaTime();
				if (m_fSelectionTimer < ConfigurationManager::Get()->timer_selectSoldiers)
					return;
				target = m_pTarget->GetActor()->getGlobalPosition();
				m_fSelectionTimer = 0.0f;
			}			
		}		
		else
		{
			return;
		}
	}
	else
	{
		return;
	}

	// find the soldier that is closest to that target
	BeePtr selected = FindSoldierClosestTo(target);
	// add the soldier to the selected soldiers list
	if (selected)
	{
		selected->SetHighlighted(true);
		selected->SetEmmitance(NiColor(0.0, 0.8, 0.0));
		m_lSelectedSoldiers.AddTail(selected);
		FSMQueenAIControl* controller = (FSMQueenAIControl*)m_control;
		((Queen*)controller->GetOwner())->RemoveSoldier(selected);
	}
}
//------------------------------------------------------------------------ 
/**
* Plays a sound when a bee is selected
*/
void StateQueenSelectSoldiers::PlaySelectionSound(Bee* bee)
{
	SoundPtr snd = (Sound*)bee->GetAttribute(GameCharacter::ATTR_SOUND_1);
	if (snd)
	{
		snd->Play();
	}
}
//------------------------------------------------------------------------ 
/**
* Finds a bee that is closest to a target
*/
BeePtr StateQueenSelectSoldiers::FindSoldierClosestTo(const NxVec3 &position)
{
	FSMQueenAIControl* controller = (FSMQueenAIControl*)m_control;
	const NiTPointerList<BeePtr>& soldiers = ((Queen*)controller->GetOwner())->GetSoldiers();

	// find min distance
	int size = soldiers.GetSize();
	NiTListIterator it = soldiers.GetHeadPos();
	NxVec3 distance;
	float minDistance = 5000000000.0f;
	BeePtr closestSoldier = 0;
	for (int i=0; i<size; i++)
	{
		BeePtr soldier = soldiers.Get(it);
		if (soldier->GetActor())
		{
			distance = position - soldier->GetActor()->getGlobalPosition();
			float mag = distance.magnitude();
			if (mag < minDistance)
			{
				minDistance = mag;
				closestSoldier = soldier;
			}
		}
		
		it = soldiers.GetNextPos(it);
				   
	}

	if (closestSoldier)
	{
		PlaySelectionSound(closestSoldier);
	}
	return closestSoldier;
}