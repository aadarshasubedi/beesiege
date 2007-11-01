/**
 * Seek behavior: The opposite of Flee. The object moves as 
 * close to the target as possible at maximum speed 
 */
#include "Seek.h"
#include "AgentInfo.h"
#include "ConfigurationManager.h"
#include <NxVec3.h>

//------------------------------------------------------------------------------------------------------
/** 
 * Ctor
 * 
 */
Seek::Seek()
{
}
//------------------------------------------------------------------------------------------------------
/** 
 * Dtor
 * 
 */
Seek::~Seek()
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
NxVec3 Seek::Execute(AgentInfoPtr aInfo)
{
	// move toward the target at maximum speed
	aInfo->m_vOrientation = aInfo->m_vTarget - aInfo->m_vPos;
	aInfo->m_vOrientation.normalize();
	aInfo->m_vDesiredVelocity = aInfo->m_vOrientation * 
		                               aInfo->m_fcMaxVelocity;

	return aInfo->m_vDesiredVelocity;
	
}
//------------------------------------------------------------------------------------------------------