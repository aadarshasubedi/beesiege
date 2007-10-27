#include "Departure.h"
#include "AgentInfo.h"
#include <NxVec3.h>
#include "ConfigurationManager.h"
using namespace std;
//------------------------------------------------------------------------------------------------------
Departure::Departure() : Behavior(string("Departure")),
m_fcKDeparture(ConfigurationManager::Get()->departure_constant)
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
	
	if (departure.magnitude() > aInfo->m_fcMaxVelocity)
	{
		aInfo->m_vOrientation = departure;
		aInfo->m_vOrientation.normalize();
		aInfo->m_vDesiredVelocity = aInfo->m_vOrientation *aInfo->m_fcMaxVelocity;
	}
	else
		aInfo->m_vDesiredVelocity = departure;

	return aInfo->m_vDesiredVelocity;
	
}
//------------------------------------------------------------------------------------------------------