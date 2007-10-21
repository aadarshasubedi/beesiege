#include "Separation.h"
#include "AgentInfo.h"
#include "Agent.h"
#include "GameManager.h"
#include "CharacterController.h"
#include <NxVec3.h>
#include <list>
using namespace std;

//------------------------------------------------------------------------------------------------------
Separation::Separation() : Behavior(string("Separation")),
						   m_fcKSeparation(2000.0f),
						   m_fcKNeighborhood(1000.0f)
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
			distanceSum += distance / distance.magnitudeSquared();
		}
	}
	
	aInfo->m_vDesiredVelocity = m_fcKSeparation * distanceSum / w;
	aInfo->m_vOrientation = aInfo->m_vDesiredVelocity;
	aInfo->m_vOrientation.normalize();

	if (aInfo->m_vDesiredVelocity.magnitude() > aInfo->m_fcMaxVelocity)
	{
		aInfo->m_vDesiredVelocity = aInfo->m_vOrientation * aInfo->m_fcMaxVelocity;
	}
	aInfo->m_fThetaDesired = aInfo->m_vOrientation.dot(NxVec3(1.0, 0.0, 0.0));

	return aInfo->m_vDesiredVelocity;
	
}
//------------------------------------------------------------------------------------------------------