#include "Arrival.h"
#include "AgentInfo.h"
#include <NxVec3.h>
#include <math.h>
#include "ConfigurationManager.h"

//------------------------------------------------------------------------------------------------------
Arrival::Arrival() : m_fcKArrival(ConfigurationManager::Get()->arrival_constant)
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
	
	if (arrival.magnitude() > aInfo->m_fcMaxVelocity)
	{
		aInfo->m_vDesiredOrientation.normalize();
		aInfo->m_vDesiredVelocity = aInfo->m_vDesiredOrientation * aInfo->m_fcMaxVelocity;
	}
	else
		aInfo->m_vDesiredVelocity = arrival;

	return aInfo->m_vDesiredVelocity;
	
}
//------------------------------------------------------------------------------------------------------