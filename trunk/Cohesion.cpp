#include "Cohesion.h"
#include "AgentInfo.h"
#include "Agent.h"
#include "GameManager.h"
#include "CharacterController.h"
#include <NxVec3.h>
#include <NxActor.h>
#include "ConfigurationManager.h"
#include <list>
using namespace std;

//------------------------------------------------------------------------------------------------------
Cohesion::Cohesion() : Behavior(string("Cohesion")),
m_fcKCohesion(ConfigurationManager::Get()->cohesion_constant),
m_fcKNeighborhood(ConfigurationManager::Get()->cohesion_radius)
{
	
}
//------------------------------------------------------------------------------------------------------
Cohesion::~Cohesion()
{
}
//------------------------------------------------------------------------------------------------------
NxVec3 Cohesion::Execute(AgentInfoPtr aInfo)
{
	
	NxVec3 distance(0.0f, 0.0f, 0.0f);
	NxVec3 positionSum(0.0f, 0.0f, 0.0f);
	float w = 1.0f;
	list<AgentPtr> agentList = GameManager::Get()->GetAgents();
	list<AgentPtr>::iterator it;
	for (it = agentList.begin(); it != agentList.end(); it++)
	{
		AgentInfoPtr otherAgent = (*it)->GetController()->GetAgentInfo();
		if (otherAgent == aInfo)
		{
			continue;
		}

		distance = aInfo->m_vPos - otherAgent->m_vPos;
		if (distance.magnitude() <= m_fcKNeighborhood)
		{
			w += 1.0f;
			positionSum += otherAgent->m_vPos;
		}
	}
	
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