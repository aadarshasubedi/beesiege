#include "BehaviorCombo.h"
#include "AgentInfo.h"
#include <NxVec3.h>
#include "GameManager.h"

//------------------------------------------------------------------------------------------------------
BehaviorCombo::BehaviorCombo (const NiTPointerList<BehaviorPtr>& behaviors, 
							   const NiTPointerList<float>& coefficients) 																														
{
	CopyLists(behaviors, m_lBehaviors);
	CopyLists(coefficients, m_lCoefficients);
}
//------------------------------------------------------------------------------------------------------
BehaviorCombo::~BehaviorCombo()
{
	m_lBehaviors.RemoveAll();	
	m_lCoefficients.RemoveAll();	
}
//------------------------------------------------------------------------------------------------------
NxVec3 BehaviorCombo::Execute(AgentInfoPtr aInfo)
{
	if (m_lBehaviors.IsEmpty() || m_lCoefficients.IsEmpty()) 
	{
		return 0;
	}

	NxVec3 desiredVel = NxVec3(0.0, 0.0, 0.0);
	NiTListIterator behaviorIter = m_lBehaviors.GetHeadPos();
	NiTListIterator coefIter = m_lCoefficients.GetHeadPos();
	
	int size = m_lBehaviors.GetSize() > m_lCoefficients.GetSize() ? m_lCoefficients.GetSize() :
																	m_lBehaviors.GetSize();
	for (int i=0; i<size; i++)
	{
		BehaviorPtr behavior = m_lBehaviors.Get(behaviorIter);
		float coefficient = m_lCoefficients.Get(coefIter);
		desiredVel += coefficient * behavior->Execute(aInfo);	
		behaviorIter = m_lBehaviors.GetNextPos(behaviorIter);
		coefIter = m_lCoefficients.GetNextPos(coefIter);
	}
	
	aInfo->m_vDesiredVelocity = desiredVel;
	aInfo->m_vOrientation = aInfo->m_vDesiredVelocity;
	aInfo->m_vOrientation.normalize();
	if (aInfo->m_vDesiredVelocity.magnitude() > aInfo->m_fcMaxVelocity)
		aInfo->m_vDesiredVelocity = aInfo->m_vOrientation * aInfo->m_fcMaxVelocity;
	
	return aInfo->m_vDesiredVelocity;
	
}
//------------------------------------------------------------------------------------------------------