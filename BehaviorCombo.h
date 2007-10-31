#ifndef BEHAVIORCOMBO_H_
#define BEHAVIORCOMBO_H_

#include "Behavior.h"
#include <NiTPointerList.h>

class BehaviorCombo : public Behavior
{
public:
	BehaviorCombo( const NiTPointerList<BehaviorPtr>& behaviors, 
			       const NiTPointerList<float>& coefficients);
	~BehaviorCombo();

	// execute the behavior
	NxVec3 Execute(AgentInfoPtr aInfo);

private:

	 NiTPointerList<BehaviorPtr> m_lBehaviors;
	 NiTPointerList<float>     m_lCoefficients;
};

NiSmartPointer(BehaviorCombo);

#endif