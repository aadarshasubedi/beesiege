/**
 * Wander behavior: the object moves randomly in a certain 
 * radius 
 */
#include "Wander.h"
#include "AgentInfo.h"
#include "ConfigurationManager.h"
#include <NxVec3.h>
#include <stdio.h>

//------------------------------------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
Wander::Wander() : m_fcKNoise(ConfigurationManager::Get()->wander_noise),
m_fcKWander(ConfigurationManager::Get()->wander_constant),
m_vWander(1.0, 0.0, 0.0)
									   
{
}
//------------------------------------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
Wander::~Wander()
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
NxVec3 Wander::Execute(AgentInfoPtr aInfo)
{
	// find a random direction
	float r1 = (float)rand() - (float)RAND_MAX/2.0f;
	float r2 = (float)rand() - (float)RAND_MAX/2.0f;
	float r3 = (float)rand() - (float)RAND_MAX/2.0f;
	NxVec3 randomDir(r1, r2, r3);
	randomDir.normalize();
	// scale it with a noise factor
	randomDir =  randomDir * m_fcKNoise;
	// change the current velocity to point to a random direction
	m_vWander = m_vWander + randomDir;
	aInfo->m_vOrientation = m_vWander;
	aInfo->m_vOrientation.normalize();
	// scale the new velocity
	m_vWander = aInfo->m_vOrientation * m_fcKWander;
	aInfo->m_vDesiredVelocity = aInfo->m_vOrientation * aInfo->m_fcMaxVelocity / 2.0f + m_vWander;
	
	if (aInfo->m_vDesiredVelocity.magnitude() > aInfo->m_fcMaxVelocity)
		aInfo->m_vDesiredVelocity = aInfo->m_vOrientation * aInfo->m_fcMaxVelocity;
	

	return aInfo->m_vDesiredVelocity;
	
}
//------------------------------------------------------------------------------------------------------