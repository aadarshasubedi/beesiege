#ifndef VELOCITYCONTROLLER_H
#define VELOCITYCONTROLLER_H

#include <NiPoint3.h>
#include "GameObj.h"

class VelocityController : public GameObj
{
public:
	// ctor / dtor
	VelocityController(float damping, float springConstant, float maxVel);
	~VelocityController();

	// updates currentVel based on desired velocity
	void Update(NiPoint3 &currentVel, const NiPoint3 &desiredVel);
	
private:

	// mass spring constants:
	// dapming
	float m_fDamping;
	// spring constant
	float m_fSpringConstant;
	// max velocity
	float m_fMaxVelocity;

};

NiSmartPointer(VelocityController);

#endif