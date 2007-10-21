#ifndef BEHAVIORCOLLECTION_H_
#define BEHAVIORCOLLECTION_H_

#include "GameObj.h"
#include <vector>

class Behavior;
NiSmartPointer(Behavior);

class BehaviorCollection : public GameObj
{
public:
	BehaviorCollection();
	~BehaviorCollection();

	BehaviorPtr GetNext();
	inline BehaviorPtr GetCurrent() const { return m_vBehaviors[m_uiCurPos]; }

private:

	std::vector<BehaviorPtr> m_vBehaviors;
	unsigned int m_uiCurPos;

};

NiSmartPointer(BehaviorCollection);
#endif