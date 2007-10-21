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
void Agent::Update(const NiPoint3& target)
{
	NxVec3 nxTarget(target.x, target.y, target.z);
	m_spController->Update(nxTarget);
}
//-------------------------------------------------------------------------