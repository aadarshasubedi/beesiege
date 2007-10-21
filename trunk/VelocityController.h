#ifndef VELOCITYCONTROLLER_H
#define VELOCITYCONTROLLER_H

#include <NiPoint3.h>
#include "GameObj.h"

class VelocityController : public GameObj
{
public:
	VelocityController(float damping, float springConstant, float maxVel);
	~VelocityController();

	void Update(NiPoint3 &currentVel, const NiPoint3 &desiredVel);
	
private:

	float m_fDamping;
	float m_fSpringConstant;
	float m_fMaxVelocity;

};

NiSmartPointer(VelocityController);

#endif