#ifndef AGENT_MGR_H_
#define AGENT_MGR_H_

#include "SingletonObj.h"
#include <list>
#include <NiSmartPointer.h>

class Agent;
class NxVec3;
class BehaviorCollection;
class Behavior;

NiSmartPointer(Agent);
NiSmartPointer(BehaviorCollection);
NiSmartPointer(Behavior);
class AgentMgr : public SingletonObj<AgentMgr>
{
	friend SingletonObj<AgentMgr>;
public:
	void AddAgent();
	void UpdateAgents(const NxVec3& target);
	void ToggleBehavior();
	void ToggleSpringDynamics();

	std::list<AgentPtr>     m_lAgents;

private:

	AgentMgr();
	~AgentMgr();
	bool                  m_bSpringDynamicsOff;
	BehaviorCollectionPtr m_spBehaviors;
	BehaviorPtr           m_spCurrentBehavior;
};

#endif