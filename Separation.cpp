#include "Separation.h"
#include "AgentInfo.h"
#include "Agent.h"
#include "GameManager.h"
#include "CharacterController.h"
#include <NxVec3.h>
#include "ConfigurationManager.h"

//------------------------------------------------------------------------------------------------------
Separation::Separation() : m_fcKSeparation(ConfigurationManager::Get()->separation_constant),
m_fcKNeighborhood(ConfigurationManager::Get()->separation_radius)
{
}
//------------------------------------------------------------------------------------------------------
Separation::~Separation()
{
}
//------------------------------------------------------------------------------------------------------
NxVec3 Separation::Execute(AgentInfoPtr aInfo)
{
	
	NxVec3 distance(0.0f, 0.0f, 0.0f);
	NxVec3 distanceSum(0.0f, 0.0f, 0.0f);
	float w = 1.0f;
	NiTListIterator it = GameManager::Get()->GetAgents().GetHeadPos();
	for (int i=0; i<GameManager::Get()->GetAgents().GetSize(); i++)
	{
		AgentPtr agent = GameManager::Get()->GetAgents().Get(it);
		AgentInfoPtr otherAgent = agent->GetController()->GetAgentInfo();
		if (otherAgent == aInfo)
		{
			it = GameManager::Get()->GetAgents().GetNextPos(it);
			continue;
		}

		distance = aInfo->m_vPos - otherAgent->m_vPos;
		if (distance.magnitude() <= m_fcKNeighborhood)
		{
			w += 1.0f;
			distanceSum += distance / distance.magnitudeSquared();
		}
		it = GameManager::Get()->GetAgents().GetNextPos(it);
	}
	
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