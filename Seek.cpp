#include "Seek.h"
#include "AgentInfo.h"
#include <NxVec3.h>
#include "ConfigurationManager.h"

//------------------------------------------------------------------------------------------------------
Seek::Seek()
{
}
//------------------------------------------------------------------------------------------------------
Seek::~Seek()
{
}
//------------------------------------------------------------------------------------------------------
NxVec3 Seek::Execute(AgentInfoPtr aInfo)
{
	
	aInfo->m_vOrientation = aInfo->m_vTarget - aInfo->m_vPos;
	aInfo->m_vOrientation.normalize();
	aInfo->m_vDesiredVelocity = aInfo->m_vOrientation * 
		                               aInfo->m_fcMaxVelocity;

	return aInfo->m_vDesiredVelocity;
	
}
//------------------------------------------------------------------------------------------------------