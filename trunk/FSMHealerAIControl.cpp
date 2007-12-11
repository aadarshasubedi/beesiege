/**
* Inherits from FSMAIControl. Controls a HealerBee
*/

#include "FSMHealerAIControl.h"
#include "FSMMachine.h"
#include "State_FollowQueen.h"
#include "HealerBee.h"
#include <NiTPointerList.h>
#include "Bee.h"
#include "Queen.h"
#include "HealthAttribute.h"
#include "GameManager.h"
#include "ConfigurationManager.h"
//-----------------------------------------------------------------------
NiImplementRTTI(FSMHealerAIControl,FSMAIControl);
//-----------------------------------------------------------------------
/**
* Ctor
* @param The bee that needs to be controlled
*/
FSMHealerAIControl::FSMHealerAIControl(HealerBee* bee) 
								:  FSMAIControl((GameCharacter*)bee),
								   m_fcRadius(ConfigurationManager::Get()->
								     healer_radius),
								   m_fcDuration(ConfigurationManager::Get()->
								     healer_duration),
								   m_fcHealAmount(ConfigurationManager::Get()->
								     healer_healAmount),
								   m_fTimer(m_fcDuration)
{
	// add states to the FSM
	StateFollowQueen* followQueen = NiNew StateFollowQueen(this);
	m_spMachine->AddState(followQueen, FSM_FOLLOW_QUEEN);
	m_spMachine->SetDefaultState(followQueen);

}
//-----------------------------------------------------------------------
/**
* Dtor
* 
*/
FSMHealerAIControl::~FSMHealerAIControl()
{
	
}
//-----------------------------------------------------------------------
/**
* Updates the required variables that the controller needs to function
* @param delta time
*/
void FSMHealerAIControl::UpdatePerceptions(float fTime)
{
	
}
//-----------------------------------------------------------------------
/**
* Performs extra updates if necessary
* @param delta time
*/
void FSMHealerAIControl::DoExtraUpdates(float fTime)
{
	m_fTimer -= m_pGameManager->GetDeltaTime();
	if (m_fTimer <= 0.0f)
	{
		GetOwner()->SetActive(false);
		return;
	}

	Heal();	
}
//-----------------------------------------------------------------------
/**
* Heals nearby allies
*/
void FSMHealerAIControl::Heal()
{
	const NiTPointerList<GameObj3dPtr>& objects =
		m_pGameManager->GetObjects();
	NiTListIterator it = objects.GetHeadPos();
	
	NxVec3 pos = GetOwner()->GetActor()->getGlobalPosition();
	NxVec3 distance;

	for (int i=0; i<objects.GetSize(); i++)
	{
		GameObj3d* obj = objects.Get(it);
		if (NiIsKindOf(Queen, obj) ||
			(NiIsKindOf(Bee, obj)))
		{
			GameCharacter* character = (GameCharacter*)obj;
			distance = character->GetActor()->getGlobalPosition() - 
					   pos;
			if (distance.magnitude() < m_fcRadius)
			{
				HealthAttribute* health = (HealthAttribute*)character->
				GetAttribute(GameCharacter::ATTR_HEALTH);
				if (health)
				{					
					health->IncreaseHealth(m_fcHealAmount);				
				}
			}
			
		}
		it = objects.GetNextPos(it);
	}
}
