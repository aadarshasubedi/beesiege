#ifndef COHESION_H_
#define COHESION_H_

#include "Behavior.h"

class Cohesion : public Behavior
{
public:
	Cohesion();
	~Cohesion();

	// execute the behavior
	NxVec3 Execute(AgentInfoPtr aInfo);

private:

	// behavior constants
	float m_fcKCohesion;
	float m_fcKNeighborhood;
};

NiSmartPointer(Cohesion);
#endif