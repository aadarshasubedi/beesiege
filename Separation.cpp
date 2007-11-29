/**
 * Separation behavior: the object tries to keep a distance from 
 * its neighbors 
 */
#include "Separation.h"
#include "AgentInfo.h"
#include "Agent.h"
#include "GameManager.h"
#include "CharacterController.h"
#include "ConfigurationManager.h"
#include <NxVec3.h>

//------------------------------------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
Separation::Separation() : m_fcKSeparation(ConfigurationManager::Get()->separation_constant),
m_fcKNeighborhood(ConfigurationManager::Get()->separation_radius), m_plNeighbors(0)
{
}
//------------------------------------------------------------------------------------------------------
/** 
 * Dtor
 * 
 */
Separation::~Separation()
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
NxVec3 Separation::Execute(AgentInfoPtr aInfo)
{
	if (!m_plNeighbors) return NxVec3(0.0f, 0.0f, 0.0f);
	
	NxVec3 distance(0.0f, 0.0f, 0.0f);
	NxVec3 distanceSum(0.0f, 0.0f, 0.0f);
	float w = 1.0f;
	// iterate through the agents
	NiTListIterator it = m_plNeighbors->GetHeadPos();
	for (int i=0; i<m_plNeighbors->GetSize(); i++)
	{
		AgentPtr agent = m_plNeighbors->Get(it);
		AgentInfoPtr otherAgent = agent->GetController()->GetAgentInfo();
		// if the other agent is this agent then skip it
		if (otherAgent == aInfo)
		{
			it = m_plNeighbors->GetNextPos(it);
			continue;
		}

		// if the other agent is in the local neighborhood
		distance = aInfo->m_vPos - otherAgent->m_vPos;
		if (distance.magnitude() <= m_fcKNeighborhood)
		{
			// increase number of agents found
			w += 1.0f;
			// increase the sum of distances
			distanceSum += distance / distance.magnitudeSquared();
		}
		it = m_plNeighbors->GetNextPos(it);
	}

	// desired velocity points away from the center of mass
	aInfo->m_vDesiredVelocity = m_fcKSeparation * distanceSum / w;
	aInfo->m_vOrientation = aInfo->m_vDesiredVelocity;
	aInfo->m_vOrientation.normalize();

	if (aInfo->m_vDesiredVelocity.magnitude() > aInfo->m_fcMaxVelocity)
	{
		aInfo->m_vDesiredVelocity = aInfo->m_vOrientation * aInfo->m_fcMaxVelocity;
	}

	return aInfo->m_vDesiredVelocity;
	
}
//------------------------------------------------------------------------------------------------------