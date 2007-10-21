#ifndef DEPARTUREL_H_
#define DEPARTUREL_H_

#include "Behavior.h"

class Departure : public Behavior
{
public:
	Departure();
	~Departure();

	// execute the behavior
	NxVec3 Execute(AgentInfoPtr aInfo);

private:

	float m_fcKDeparture;
};

NiSmartPointer(Departure);

#endif