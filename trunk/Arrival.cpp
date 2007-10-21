#include "Arrival.h"
#include "AgentInfo.h"
#include <NxVec3.h>
#include <math.h>
using namespace std;
//------------------------------------------------------------------------------------------------------
Arrival::Arrival() : Behavior(string("Arrival")),
					 m_fcKArrival(10.0f)
{
}
//------------------------------------------------------------------------------------------------------
Arrival::~Arrival()
{
}
//------------------------------------------------------------------------------------------------------
NxVec3 Arrival::Execute(AgentInfoPtr aInfo)
{
	
	aInfo->m_vDesiredOrientation = aInfo->m_vTarget - aInfo->m_vPos;
	NxVec3 arrival = m_fcKArrival * aInfo->m_vDesiredOrientation;
	aInfo->m_vDesiredOrientation.normalize();

	if (arrival.magnitude() > aInfo->m_fcMaxVelocity)
		aInfo->m_vDesiredVelocity = aInfo->m_vDesiredOrientation * aInfo->m_fcMaxVelocity;
	else
		aInfo->m_vDesiredVelocity = arrival;

	aInfo->m_fVelocityDesired = aInfo->m_vDesiredVelocity.magnitude();
	aInfo->m_fYawDesired = atan2(aInfo->m_vDesiredVelocity[2], aInfo->m_vDesiredVelocity[0]) ;
	aInfo->m_fPitchDesired = atan2(aInfo->m_vDesiredVelocity[1], aInfo->m_vDesiredVelocity[0]) - 3.14f/2.0f;

	return aInfo->m_vDesiredVelocity;
	
}
//------------------------------------------------------------------------------------------------------