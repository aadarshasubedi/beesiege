#include "Departure.h"
#include "AgentInfo.h"
#include <NxVec3.h>
using namespace std;
//------------------------------------------------------------------------------------------------------
Departure::Departure() : Behavior(string("Departure")),
						 m_fcKDeparture(800.0f)
{
}
//------------------------------------------------------------------------------------------------------
Departure::~Departure()
{
}
//------------------------------------------------------------------------------------------------------
NxVec3 Departure::Execute(AgentInfoPtr aInfo)
{
	
	NxVec3 departure;

	NxVec3 e = aInfo->m_vTarget - aInfo->m_vPos;
	e = -e / e.magnitudeSquared();
	departure = m_fcKDeparture*e;
	aInfo->m_vOrientation = departure;
	aInfo->m_vOrientation.normalize();

	if (departure.magnitude() > aInfo->m_fcMaxVelocity)
		aInfo->m_vDesiredVelocity = aInfo->m_vOrientation *aInfo->m_fcMaxVelocity;
	else
		aInfo->m_vDesiredVelocity = departure;
	
	aInfo->m_fThetaDesired = aInfo->m_vOrientation.dot(NxVec3(1.0, 0.0, 0.0));

	return aInfo->m_vDesiredVelocity;
	
}
//------------------------------------------------------------------------------------------------------