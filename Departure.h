#ifndef DEPARTUREL_H_
#define DEPARTUREL_H_

#include "Behavior.h"
#include <NxVec3.h>

class Departure : public Behavior
{
public:
	Departure();
	~Departure();

	// execute the behavior
	NxVec3 Execute(AgentInfoPtr aInfo);

private:

	// behavior constants
	float m_fcKDeparture;
};

NiSmartPointer(Departure);

#endif