/**
 * Departure behavior: the object is repeled from a certain 
 * target if it comes close enough to the object 
 */
#include "Departure.h"
#include "AgentInfo.h"
#include "ConfigurationManager.h"
#include "GameManager.h"
#include <NxVec3.h>

//------------------------------------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
Departure::Departure() : m_fcKDeparture(ConfigurationManager::Get()->departure_constant)
{
}
//------------------------------------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
Departure::~Departure()
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
NxVec3 Departure::Execute(AgentInfoPtr aInfo)
{
	
	NxVec3 departure;
	// desired velocity points away from the target
	NxVec3 e;
	e = aInfo->m_vTarget - aInfo->m_vPos;
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