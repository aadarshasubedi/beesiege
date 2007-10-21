#ifndef ARRIVAL_H_
#define ARRIVAL_H_

#include "Behavior.h"

class Arrival : public Behavior
{
public:
	Arrival();
	~Arrival();

	// execute the behavior
	NxVec3 Execute(AgentInfoPtr aInfo);

private:

	float m_fcKArrival;
};

NiSmartPointer(Arrival);
#endif