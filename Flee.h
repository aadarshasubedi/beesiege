#ifndef FLEE_H_
#define FLEE_H_

#include "Behavior.h"

class Flee : public Behavior
{
public:
	Flee();
	~Flee();

	// execute the behavior
	NxVec3 Execute(AgentInfoPtr aInfo);
};

NiSmartPointer(Flee);
#endif