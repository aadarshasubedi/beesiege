/**
*	A state that allows the queen to select Gatherers
*/
#include "StateQueenSelectGatherers.h"
#include "Queen.h"
#include "FSMMachine.h"
#include "GameManager.h"
#include "FSMQueenAIControl.h"
#include "ConfigurationManager.h"
#include "Flower.h"
#include "Sound.h"
#include <NiPhysX.h>

//----------------------------------------------------------------------
/**
*	Ctor
*/
StateQueenSelectGatherers::StateQueenSelectGatherers(FSMAIControl* control, 
												   int type)
: FSMState(control, type), m_pTarget(0)
{
}

//----------------------------------------------------------------------
/**
*	Dtor
*/
StateQueenSelectGatherers::~StateQueenSelectGatherers()
{
	m_lSelectedGatherers.RemoveAll();
}
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is entered
*/
void StateQueenSelectGatherers::Enter()
{
	m_fSelectionTimer = ConfigurationManager::Get()->timer_selectSoldiers;
	m_pTarget = GameManager::Get()->GetCurrentFlowerTarget();

}
//----------------------------------------------------------------------
/**
*	Updates the state
*   @param delta time
*/
void StateQueenSelectGatherers::Update(float fTime)
{
	IsOwnerDead();

	FSMQueenAIControl* controller = (FSMQueenAIControl*)m_control;
	NIASSERT(controller);

	if (controller->issuedSelectGatherersCommand)
	{
		controller->issuedSelectGatherersCommand = false;
		SelectMoreGatherers();
	}

}
//----------------------------------------------------------------------
/**
*	Checks for transition conditions
*   @param delta time
*/
FSMState* StateQueenSelectGatherers::CheckTransitions(float fTime)
{
	FSMQueenAIControl* controller = (FSMQueenAIControl*)m_control;
	NIASSERT(controller);
	FSMState* nextState = controller->GetMachine()->GetCurrentState();;
	
	if (controller->issuedGatherCommand ||
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
void StateQueenSelectGatherers::Exit()
{
	// command selected Gatherers to attack
	if (!m_lSelectedGatherers.IsEmpty() && m_pTarget)
	{
		NiTListIterator it = m_lSelectedGatherers.GetHeadPos();
		for (int i=0; i<m_lSelectedGatherers.GetSize(); i++)
		{
			m_lSelectedGatherers.Get(it)->SetGather(m_pTarget);
			m_lSelectedGatherers.Get(it)->SetEmmitance(NiColor(0.0, 0.0, 0.0));
			it = m_lSelectedGatherers.GetNextPos(it);
		}
	}
	m_pTarget = 0;
	
	m_lSelectedGatherers.RemoveAll();
}
//------------------------------------------------------------------------ 
/** 
 * Targets next closest enemy
 * 
 */
void StateQueenSelectGatherers::SelectMoreGatherers()
{
	// get the target's position
	NxVec3 target;
	if (m_pTarget)
	{
		m_fSelectionTimer += GameManager::Get()->GetDeltaTime();
		if (m_fSelectionTimer < ConfigurationManager::Get()->timer_selectSoldiers)
			return;
		NiPoint3 pos = m_pTarget->GetNode()->GetTranslate();
		target = NxVec3(pos.x, pos.y, pos.z);
		m_fSelectionTimer = 0.0f;			
	}
	else
	{
		return;
	}

	// find the soldier that is closest to that target
	HoneyBeePtr selected = FindGathererClosestTo(target);
	// add the soldier to the selected Gatherers list
	if (selected)
	{
		selected->SetEmmitance(NiColor(0.7, 0.8, 0.0));
		m_lSelectedGatherers.AddTail(selected);
		FSMQueenAIControl* controller = (FSMQueenAIControl*)m_control;
		((Queen*)controller->GetOwner())->RemoveGatherer(selected);
	}
}
//------------------------------------------------------------------------ 
/**
* Plays a sound when a bee is selected
*/
void StateQueenSelectGatherers::PlaySelectionSound(HoneyBee* bee)
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
HoneyBeePtr StateQueenSelectGatherers::FindGathererClosestTo(const NxVec3 &position)
{
	FSMQueenAIControl* controller = (FSMQueenAIControl*)m_control;
	const NiTPointerList<HoneyBeePtr>& Gatherers = ((Queen*)controller->GetOwner())->GetGatherers();

	// find min distance
	int size = Gatherers.GetSize();
	NiTListIterator it = Gatherers.GetHeadPos();
	NxVec3 distance;
	float minDistance = 5000000000.0f;
	HoneyBeePtr closest = 0;
	for (int i=0; i<size; i++)
	{
		HoneyBeePtr current = Gatherers.Get(it);
		if (current->GetActor())
		{
			distance = position - current->GetActor()->getGlobalPosition();
			float mag = distance.magnitude();
			if (mag < minDistance)
			{
				minDistance = mag;
				closest = current;
			}
		}
		
		it = Gatherers.GetNextPos(it);
				   
	}

	if (closest)
	{
		PlaySelectionSound(closest);
	}

	return closest;
}