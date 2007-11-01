/**
 * Alignment behavior: The object follows the general direction 
 * of its neighbors 
 */

#include "Alignment.h"
#include "AgentInfo.h"
#include "Agent.h"
#include "GameManager.h"
#include "CharacterController.h"
#include "ConfigurationManager.h"
#include <NxVec3.h>
#include <NxActor.h>

//------------------------------------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
Alignment::Alignment() : m_fcKAlignment(ConfigurationManager::Get()->alignment_constant),
m_fcKNeighborhood(ConfigurationManager::Get()->alignment_radius)
{
	
}
//------------------------------------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
Alignment::~Alignment()
{
}
//------------------------------------------------------------------------------------------------------ 
/** 
 * Executes the behavior
 * 
 * @param aInfo
 * 
 * @return NxVec3
 */
NxVec3 Alignment::Execute(AgentInfoPtr aInfo)
{
	
	NxVec3 distance(0.0f, 0.0f, 0.0f);
	NxVec3 velocitySum(0.0f, 0.0f, 0.0f);
	float w = 1.0f;
	// iterate through the neighboring agents
	NiTListIterator it = GameManager::Get()->GetAgents().GetHeadPos();
	for (int i=0; i<GameManager::Get()->GetAgents().GetSize(); i++)
	{
		AgentPtr agent = GameManager::Get()->GetAgents().Get(it);
		AgentInfoPtr otherAgent = agent->GetController()->GetAgentInfo();
		// if this is the current agent then move on to the next one
		if (otherAgent == aInfo)
		{
			it = GameManager::Get()->GetAgents().GetNextPos(it);
			continue;
		}
		// check if the other agent is in the local neighborhood
		distance = aInfo->m_vPos - otherAgent->m_vPos;
		if (distance.magnitude() <= m_fcKNeighborhood)
		{
			// increase the number of agents found in the neighborhood
			w += 1.0f;
			// increase the sum of velocities
			velocitySum += agent->GetActor()->getLinearVelocity();
		}
		it = GameManager::Get()->GetAgents().GetNextPos(it);
	}

	// compute desired velocity
	aInfo->m_vDesiredVelocity = m_fcKAlignment * velocitySum / w;
	// compute desired orientation
	aInfo->m_vOrientation = aInfo->m_vDesiredVelocity;
	aInfo->m_vOrientation.normalize();
	// constrain velocity
	if (aInfo->m_vDesiredVelocity.magnitude() > aInfo->m_fcMaxVelocity)
	{
		aInfo->m_vDesiredVelocity = aInfo->m_vOrientation * aInfo->m_fcMaxVelocity;
	}
	// return desired velocity
	return aInfo->m_vDesiredVelocity;
}
//------------------------------------------------------------------------------------------------------