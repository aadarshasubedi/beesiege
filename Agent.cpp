#include "Agent.h"
#include "CharacterController.h"
#include <NxActor.h>
//-------------------------------------------------------------------------
Agent::Agent(NxActor* actor) : m_pActor(actor)
{
	m_spController = NiNew CharacterController(this);	
}
//-------------------------------------------------------------------------
Agent::~Agent()
{
	m_spController = 0;
}
//-------------------------------------------------------------------------
void Agent::Update(const NxVec3& target)
{
	m_spController->Update(target);
}
//-------------------------------------------------------------------------