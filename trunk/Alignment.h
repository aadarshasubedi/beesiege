#ifndef ALIGNMENT_H_
#define ALIGNMENT_H_

#include "Behavior.h"
#include <NiTPointerList.h>

class Agent;
NiSmartPointer(Agent);

class Alignment : public Behavior
{
public:
	Alignment();
	~Alignment();

	// execute the behavior
	NxVec3 Execute(AgentInfoPtr aInfo);

	// setters
	void SetNeighbors (const NiTPointerList<AgentPtr>* agents)
	{
		m_plNeighbors = agents;
	}

private:

	// behavior constants
	float m_fcKAlignment;
	float m_fcKNeighborhood;

	// neighbors
	const NiTPointerList<AgentPtr>* m_plNeighbors;
};

NiSmartPointer(Alignment);
#endif