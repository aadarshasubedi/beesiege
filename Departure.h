#ifndef DEPARTUREL_H_
#define DEPARTUREL_H_

#include "Behavior.h"
#include <NxVec3.h>

class Departure : public Behavior
{
public:
	Departure();
	Departure(bool bAvoidCamera);
	~Departure();

	// execute the behavior
	NxVec3 Execute(AgentInfoPtr aInfo);

private:

	float m_fcKDeparture;
	NxVec3 m_vCameraPosition;
	bool m_bAvoidCamera;
};

NiSmartPointer(Departure);

#endif