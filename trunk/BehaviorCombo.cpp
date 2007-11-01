/**
 * A BehaviorCombo is a combination of behaviors. The final 
 * desired velocity = Sum (behavior[i]->desiredVel * 
 * behavior[i]->Coefficient) 
 */
#include "BehaviorCombo.h"
#include "AgentInfo.h"
#include "GameManager.h"
#include <NxVec3.h>

//------------------------------------------------------------------------------------------------------
/** 
 * Ctor
 * 
 * @param behaviors
 * @param coefficients
 */
BehaviorCombo::BehaviorCombo (const NiTPointerList<BehaviorPtr>& behaviors, 
							   const NiTPointerList<float>& coefficients) 																														
{
	CopyLists(behaviors, m_lBehaviors);
	CopyLists(coefficients, m_lCoefficients);
}
//------------------------------------------------------------------------------------------------------
/** 
 * Dtor
 * 
 */
BehaviorCombo::~BehaviorCombo()
{
	m_lBehaviors.RemoveAll();	
	m_lCoefficients.RemoveAll();	
}
//------------------------------------------------------------------------------------------------------ 
/** 
 * Executes the behavior
 * 
 * @param aInfo
 * 
 * @return NxVec3
 */
NxVec3 BehaviorCombo::Execute(AgentInfoPtr aInfo)
{
	// check if one of the behavior or coefficient lists is empty
	if (m_lBehaviors.IsEmpty() || m_lCoefficients.IsEmpty()) 
	{
		return 0;
	}

	// iterate through the behaviors and respective coefficients
	NxVec3 desiredVel = NxVec3(0.0, 0.0, 0.0);
	NiTListIterator behaviorIter = m_lBehaviors.GetHeadPos();
	NiTListIterator coefIter = m_lCoefficients.GetHeadPos();
	
	int size = m_lBehaviors.GetSize() > m_lCoefficients.GetSize() ? m_lCoefficients.GetSize() :
																	m_lBehaviors.GetSize();
	for (int i=0; i<size; i++)
	{
		// increase the desired velocity by executing each of the
		// behaviors and getting the desired velocity that each one of
		// them generates. The velocity of each behavior is multiplied
		// with a coefficient
		BehaviorPtr behavior = m_lBehaviors.Get(behaviorIter);
		float coefficient = m_lCoefficients.Get(coefIter);
		desiredVel += coefficient * behavior->Execute(aInfo);	
		behaviorIter = m_lBehaviors.GetNextPos(behaviorIter);
		coefIter = m_lCoefficients.GetNextPos(coefIter);
	}

	// set desired velocity and orientation
	aInfo->m_vDesiredVelocity = desiredVel;
	aInfo->m_vOrientation = aInfo->m_vDesiredVelocity;
	aInfo->m_vOrientation.normalize();
	if (aInfo->m_vDesiredVelocity.magnitude() > aInfo->m_fcMaxVelocity)
		aInfo->m_vDesiredVelocity = aInfo->m_vOrientation * aInfo->m_fcMaxVelocity;
	
	return aInfo->m_vDesiredVelocity;
	
}
//------------------------------------------------------------------------------------------------------