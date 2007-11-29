#ifndef SEPARATION_H_
#define SEPARATION_H_

#include "Behavior.h"
#include <NiTPointerList.h>

class Agent;
NiSmartPointer(Agent);

class Separation : public Behavior
{
public:
	Separation();
	~Separation();

	// execute the behavior
	NxVec3 Execute(AgentInfoPtr aInfo);

	// setters
	void SetNeighbors (const NiTPointerList<AgentPtr>* agents)
	{
		m_plNeighbors = agents;
	}

private:

	// behavior constants
	float m_fcKSeparation;
	float m_fcKNeighborhood;

	// neighbors
	const NiTPointerList<AgentPtr>* m_plNeighbors;
};

NiSmartPointer(Separation);
#endif