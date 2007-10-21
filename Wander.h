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

	float  m_fcKNoise;
	float  m_fcKWander;
	NxVec3 m_vWander;
};

NiSmartPointer(Wander);

#endif