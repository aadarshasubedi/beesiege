#ifndef WANDER_H_
#define WANDER_H_

#include "Behavior.h"
#include <NxVec3.h>

class Wander : public Behavior
{
public:
	Wander();
	~Wander();

	// execute the behavior
	NxVec3 Execute(AgentInfoPtr aInfo);

private:

	// behavior constants
	float  m_fcKNoise;
	float  m_fcKWander;
	// the current direction
	NxVec3 m_vWander;
};

NiSmartPointer(Wander);

#endif