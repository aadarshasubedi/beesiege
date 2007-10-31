#include "Flee.h"
#include "AgentInfo.h"
#include <NxVec3.h>
#include "ConfigurationManager.h"

//------------------------------------------------------------------------------------------------------
Flee::Flee()
{
}
//------------------------------------------------------------------------------------------------------
Flee::~Flee()
{
}
//------------------------------------------------------------------------------------------------------
NxVec3 Flee::Execute(AgentInfoPtr aInfo)
{
	
	aInfo->m_vOrientation = aInfo->m_vTarget - aInfo->m_vPos;
	aInfo->m_vOrientation.normalize();
	aInfo->m_vDesiredVelocity = -aInfo->m_vOrientation * 
		                               aInfo->m_fcMaxVelocity;

	return aInfo->m_vDesiredVelocity;
	
}
//------------------------------------------------------------------------------------------------------