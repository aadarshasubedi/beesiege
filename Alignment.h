#ifndef ALIGNMENT_H_
#define ALIGNMENT_H_

#include "Behavior.h"

class Alignment : public Behavior
{
public:
	Alignment();
	~Alignment();

	// execute the behavior
	NxVec3 Execute(AgentInfoPtr aInfo);

private:

	// behavior constants
	float m_fcKAlignment;
	float m_fcKNeighborhood;
};

NiSmartPointer(Alignment);
#endif