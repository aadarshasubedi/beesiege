/**
*	A FSM state
*/

#include "FSMState.h"
#include "FSMAIControl.h"
#include "HealthAttribute.h"
#include "GameManager.h"
#include "Bee.h"
#include "HealerBee.h"
#include "HoneyBee.h"
//------------------------------------------------------
/**
* Ctor
*/
FSMState::FSMState(FSMAIControl* control, int type) :
 m_type(type),
 m_control(control),
 m_pGameManager(GameManager::Get())
{ 
	m_pOwnerHealth = (HealthAttribute*)m_control->GetOwner()->
		GetAttribute(GameCharacter::ATTR_HEALTH);
	
}
//------------------------------------------------------
/**
* Dtor
*/
FSMState::~FSMState()
{
 if (m_control)
 {
	 m_control  = 0;
 }
}
//------------------------------------------------------
/**
* Checks if owner is dead and sets it to non-active if yes
*/
bool FSMState::IsOwnerDead()
{
	if (m_pOwnerHealth)
	{
		if (m_pOwnerHealth->GetHealth() <= 0.0f)
		{
			GameCharacter* owner = m_control->GetOwner();
			owner->SetActive(false);
			if (NiIsKindOf(Bee, owner))
			{
				m_pGameManager->GetQueen()->RemoveSoldier((Bee*)owner);
			}
			else if (NiIsKindOf(HealerBee, owner))
			{
				m_pGameManager->GetQueen()->RemoveHealer((HealerBee*)owner);
			}
			else if (NiIsKindOf(HoneyBee, owner))
			{
				m_pGameManager->GetQueen()->RemoveGatherer((HoneyBee*)owner);
			}
			return true;
		}
	}
	else
	{
 		return false;
	}

	return false;
}
