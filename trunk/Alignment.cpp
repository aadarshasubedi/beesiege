#include "Alignment.h"
#include "AgentInfo.h"
#include "Agent.h"
#include "GameManager.h"
#include "CharacterController.h"
#include <NxVec3.h>
#include <NxActor.h>
#include "ConfigurationManager.h"

//------------------------------------------------------------------------------------------------------
Alignment::Alignment() : m_fcKAlignment(ConfigurationManager::Get()->alignment_constant),
m_fcKNeighborhood(ConfigurationManager::Get()->alignment_radius)
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
			velocitySum += agent->GetActor()->getLinearVelocity();
		}
		it = GameManager::Get()->GetAgents().GetNextPos(it);
	}
	
	aInfo->m_vDesiredVelocity = m_fcKAlignment * velocitySum / w;
	aInfo->m_vOrientation = aInfo->m_vDesiredVelocity;
	aInfo->m_vOrientation.normalize();

	if (aInfo->m_vDesiredVelocity.magnitude() > aInfo->m_fcMaxVelocity)
	{
		aInfo->m_vDesiredVelocity = aInfo->m_vOrientation * aInfo->m_fcMaxVelocity;
	}

	return aInfo->m_vDesiredVelocity;
}
//------------------------------------------------------------------------------------------------------