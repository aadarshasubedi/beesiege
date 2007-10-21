#include "Wander.h"
#include "AgentInfo.h"
#include <NxVec3.h>
#include <stdio.h>
using namespace std;
//------------------------------------------------------------------------------------------------------
Wander::Wander() : Behavior(string("Wander")),
				   m_fcKNoise(10.0f),
				   m_fcKWander(10.0f),
				   m_vWander(1.0, 0.0, 0.0)
									   
{
}
//------------------------------------------------------------------------------------------------------
Wander::~Wander()
{
}
//------------------------------------------------------------------------------------------------------
NxVec3 Wander::Execute(AgentInfoPtr aInfo)
{
	
	float r1 = (float)rand() - (float)RAND_MAX/2.0f;
	float r2 = (float)rand() - (float)RAND_MAX/2.0f;
	float r3 = (float)rand() - (float)RAND_MAX/2.0f;
	NxVec3 randomDir(r1, r2, r3);
	randomDir.normalize();
	randomDir =  randomDir * m_fcKNoise;
	m_vWander = m_vWander + randomDir;
	aInfo->m_vOrientation = m_vWander;
	aInfo->m_vOrientation.normalize();
	m_vWander = aInfo->m_vOrientation * m_fcKWander;
	aInfo->m_vDesiredVelocity = aInfo->m_vOrientation * aInfo->m_fcMaxVelocity / 2.0f + m_vWander;
	
	if (aInfo->m_vDesiredVelocity.magnitude() > aInfo->m_fcMaxVelocity)
		aInfo->m_vDesiredVelocity = aInfo->m_vOrientation * aInfo->m_fcMaxVelocity;
	
	
	aInfo->m_fThetaDesired = aInfo->m_vOrientation.dot(NxVec3(1.0, 0.0, 0.0));

	return aInfo->m_vDesiredVelocity;
	
}
//------------------------------------------------------------------------------------------------------