#ifndef BEHAVIORCOMBO_H_
#define BEHAVIORCOMBO_H_

#include "Behavior.h"
#include <list>

class BehaviorCombo : public Behavior
{
public:
	BehaviorCombo(const std::string& type, 
				  const std::list<BehaviorPtr>& behaviors, 
			      const std::list<float>& coefficients);
	~BehaviorCombo();

	// execute the behavior
	NxVec3 Execute(AgentInfoPtr aInfo);

private:

	std::list<BehaviorPtr> m_lBehaviors;
	std::list<float>     m_lCoefficients;
};

NiSmartPointer(BehaviorCombo);

#endif