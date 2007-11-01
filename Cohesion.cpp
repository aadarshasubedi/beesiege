/**
 * Cohesion behavior: the object tries to move toward the the 
 * center of mass of its local neighborhood 
 */
#include "Cohesion.h"
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
Cohesion::Cohesion() : m_fcKCohesion(ConfigurationManager::Get()->cohesion_constant),
m_fcKNeighborhood(ConfigurationManager::Get()->cohesion_radius)
{
	
}
//------------------------------------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
Cohesion::~Cohesion()
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
NxVec3 Cohesion::Execute(AgentInfoPtr aInfo)
{
	
	NxVec3 distance(0.0f, 0.0f, 0.0f);
	NxVec3 positionSum(0.0f, 0.0f, 0.0f);
	float w = 1.0f;
	// iterate through the all the agents
	NiTListIterator it = GameManager::Get()->GetAgents().GetHeadPos();
	for (int i=0; i<GameManager::Get()->GetAgents().GetSize(); i++)
	{
		AgentPtr agent = GameManager::Get()->GetAgents().Get(it);
		AgentInfoPtr otherAgent = agent->GetController()->GetAgentInfo();
		// if the other agent is the current one then skip it
		if (otherAgent == aInfo)
		{
			it = GameManager::Get()->GetAgents().GetNextPos(it);
			continue;
		}
		// if other agent is in local neighborhood
		distance = aInfo->m_vPos - otherAgent->m_vPos;
		if (distance.magnitude() <= m_fcKNeighborhood)
		{
			// increase number of agents found
			w += 1.0f;
			// add the other agent's position to the sum
			positionSum += otherAgent->m_vPos;
		}
		it = GameManager::Get()->GetAgents().GetNextPos(it);
	}

	// desired velocity points towards the center of mass of the
	// neighborhood
	aInfo->m_vDesiredVelocity = m_fcKCohesion * (positionSum / w - aInfo->m_vPos);
	aInfo->m_vOrientation = aInfo->m_vDesiredVelocity;
	aInfo->m_vOrientation.normalize();

	if (aInfo->m_vDesiredVelocity.magnitude() > aInfo->m_fcMaxVelocity)
	{
		aInfo->m_vDesiredVelocity = aInfo->m_vOrientation * aInfo->m_fcMaxVelocity;
	}

	return aInfo->m_vDesiredVelocity;
}
//------------------------------------------------------------------------------------------------------