#include "VelocityController.h"

VelocityController::VelocityController(float damping, float springConstant, float maxVel)
: m_fDamping(damping), m_fSpringConstant(springConstant), m_fMaxVelocity(maxVel)
{

}

VelocityController::~VelocityController()
{
}

void VelocityController::Update(NiPoint3 &currentVel, const NiPoint3 &desiredVel)
{
	float curVel = currentVel.Length();
	float force  = m_fSpringConstant * (m_fDamping*desiredVel.Length() - curVel);
	float newVel =  curVel + force;
	
	if (newVel < 0.0f)
	{
		newVel = newVel < -m_fMaxVelocity ? -m_fMaxVelocity : newVel;
	}
	else if (newVel > 0.0f)
	{
		newVel = newVel > m_fMaxVelocity ? m_fMaxVelocity : newVel;
	}

	NiPoint3 heading = desiredVel;
	heading.Unitize();
	currentVel = newVel * heading;

}