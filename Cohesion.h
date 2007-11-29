#ifndef COHESION_H_
#define COHESION_H_

#include "Behavior.h"
#include <NiTPointerList.h>

class Agent;
NiSmartPointer(Agent);

class Cohesion : public Behavior
{
public:
	Cohesion();
	~Cohesion();

	// execute the behavior
	NxVec3 Execute(AgentInfoPtr aInfo);

	// setters
	void SetNeighbors (const NiTPointerList<AgentPtr>* agents)
	{
		m_plNeighbors = agents;
	}

private:

	// behavior constants
	float m_fcKCohesion;
	float m_fcKNeighborhood;

	// neighbors
	const NiTPointerList<AgentPtr>* m_plNeighbors;
};

NiSmartPointer(Cohesion);
#endif