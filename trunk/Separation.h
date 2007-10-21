#ifndef SEPARATION_H_
#define SEPARATION_H_

#include "Behavior.h"

class Separation : public Behavior
{
public:
	Separation();
	~Separation();

	// execute the behavior
	NxVec3 Execute(AgentInfoPtr aInfo);

private:

	float m_fcKSeparation;
	float m_fcKNeighborhood;
};

NiSmartPointer(Separation);
#endif