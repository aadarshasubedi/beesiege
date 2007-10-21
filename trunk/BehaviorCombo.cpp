#include "BehaviorCombo.h"
#include "AgentInfo.h"
#include <NxVec3.h>
using namespace std;
//------------------------------------------------------------------------------------------------------
BehaviorCombo::BehaviorCombo (const string& type, 
							  const list<BehaviorPtr>& behaviors, 
							  const list<float>& coefficients) : Behavior(type),
																 m_lBehaviors(behaviors),
																 m_lCoefficients(coefficients)
																	
{

}
//------------------------------------------------------------------------------------------------------
BehaviorCombo::~BehaviorCombo()
{
	list<BehaviorPtr>::iterator behaviorIter;
	for (behaviorIter = m_lBehaviors.begin(); behaviorIter != m_lBehaviors.end(); behaviorIter++)
	{
		(*behaviorIter) = 0;
	}
	m_lBehaviors.clear();
	
	m_lCoefficients.clear();
}
//------------------------------------------------------------------------------------------------------
NxVec3 BehaviorCombo::Execute(AgentInfoPtr aInfo)
{

	NxVec3 desiredVel = NxVec3(0.0, 0.0, 0.0);
	list<BehaviorPtr>::iterator behaviorIter;
	list<float>::iterator coefIter;
	
	for (behaviorIter  = m_lBehaviors.begin(), 
		 coefIter      = m_lCoefficients.begin(); 
		 behaviorIter != m_lBehaviors.end() && 
		 coefIter     != m_lCoefficients.end(); 
		 behaviorIter++, coefIter++)
	{
		desiredVel += (*coefIter) * (*behaviorIter)->Execute(aInfo);	 
	}
	
	aInfo->m_vDesiredVelocity = desiredVel;
	aInfo->m_vOrientation = aInfo->m_vDesiredVelocity;
	aInfo->m_vOrientation.normalize();
	if (aInfo->m_vDesiredVelocity.magnitude() > aInfo->m_fcMaxVelocity)
		aInfo->m_vDesiredVelocity = aInfo->m_vOrientation * aInfo->m_fcMaxVelocity;
	
	return aInfo->m_vDesiredVelocity;
	
	
}
//------------------------------------------------------------------------------------------------------