#include "Alignment.h"
#include "AgentInfo.h"
#include "Agent.h"
#include "GameManager.h"
#include "CharacterController.h"
#include <NxVec3.h>
#include <NxActor.h>
#include <list>
using namespace std;

//------------------------------------------------------------------------------------------------------
Alignment::Alignment() : Behavior(string("Alignment")),
						 m_fcKAlignment(100.0f),
						 m_fcKNeighborhood(50.0f)
{
	
}
//------------------------------------------------------------------------------------------------------
Alignment::~Alignment()
{
}
//------------------------------------------------------------------------------------------------------
NxVec3 Alignment::Execute(AgentInfoPtr aInfo)
{
	
	NxVec3 distance(0.0f, 0.0f, 0.0f);
	NxVec3 velocitySum(0.0f, 0.0f, 0.0f);
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
			velocitySum += (*it)->GetActor()->getLinearVelocity();
		}
	}
	
	aInfo->m_vDesiredVelocity = m_fcKAlignment * velocitySum / w;
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