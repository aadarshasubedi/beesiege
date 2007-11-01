/**
 * Arrival behavior: the object moves toward the target and 
 * slows down as it reaches it 
 */
#include "Arrival.h"
#include "AgentInfo.h"
#include "ConfigurationManager.h"
#include <NxVec3.h>
#include <math.h>
//------------------------------------------------------------------------------------------------------
/** 
 * Ctor
 * 
 */
Arrival::Arrival() : m_fcKArrival(ConfigurationManager::Get()->arrival_constant)
{
}
//------------------------------------------------------------------------------------------------------
/** 
 * Dtor
 * 
 */
Arrival::~Arrival()
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
NxVec3 Arrival::Execute(AgentInfoPtr aInfo)
{
	// find desired orientation
	aInfo->m_vDesiredOrientation = aInfo->m_vTarget - aInfo->m_vPos;
	// find desired velocity
	NxVec3 arrival = m_fcKArrival * aInfo->m_vDesiredOrientation;
	// constrain desired velocity
	if (arrival.magnitude() > aInfo->m_fcMaxVelocity)
	{
		aInfo->m_vDesiredOrientation.normalize();
		aInfo->m_vDesiredVelocity = aInfo->m_vDesiredOrientation * aInfo->m_fcMaxVelocity;
	}
	else
		aInfo->m_vDesiredVelocity = arrival;

	// retun desired velocity
	return aInfo->m_vDesiredVelocity;
	
}
//------------------------------------------------------------------------------------------------------