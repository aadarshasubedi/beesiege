/**
 * Flee behavior: the opposite of Seek. The object runs as far 
 * away as possible from a target 
 */
#include "Flee.h"
#include "AgentInfo.h"
#include "ConfigurationManager.h"
#include <NxVec3.h>

//------------------------------------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
Flee::Flee()
{
}
//------------------------------------------------------------------------------------------------------
/** 
 * Dtor
 * 
 */
Flee::~Flee()
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
NxVec3 Flee::Execute(AgentInfoPtr aInfo)
{
	// desired velocity is constant and points away from the target
	aInfo->m_vOrientation = aInfo->m_vTarget - aInfo->m_vPos;
	aInfo->m_vOrientation.normalize();
	aInfo->m_vDesiredVelocity = -aInfo->m_vOrientation * 
		                               aInfo->m_fcMaxVelocity;

	return aInfo->m_vDesiredVelocity;
	
}
//------------------------------------------------------------------------------------------------------