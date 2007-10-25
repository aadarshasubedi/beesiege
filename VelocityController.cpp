#include "VelocityController.h"
#include <math.h>

VelocityController::VelocityController(float damping, float springConstant, float maxVel)
: m_fDamping(damping), m_fSpringConstant(springConstant), m_fMaxVelocity(maxVel)
{

}

VelocityController::~VelocityController()
{
}

void VelocityController::Update(NiPoint3 &currentVel, const NiPoint3 &desiredVel)
{
	NiPoint3 force  = -m_fSpringConstant * (desiredVel - currentVel) + m_fDamping*currentVel; 
	NiPoint3 newVel =  currentVel - force*0.1;
	
	float newVelLength = newVel.Length();
	
	if (newVelLength < 0.0f)
	{
		if (newVelLength < -m_fMaxVelocity)
		{
			NiPoint3 heading = newVel;
			heading.Unitize();	
			newVel = -m_fMaxVelocity*heading;
		}
	}
	else if (newVelLength > 0.0f)
	{
		if (newVelLength > m_fMaxVelocity)
		{
			NiPoint3 heading = newVel;
			heading.Unitize();	
			newVel = m_fMaxVelocity*heading;
		}
	}

	
	currentVel = newVel;

}