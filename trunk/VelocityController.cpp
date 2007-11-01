/**
 * Implements a mass-spring controller that modifies a certain 
 * velocity given a desired velocity 
 */
#include "VelocityController.h"
#include <math.h>

//-------------------------------------------------------------------------------------------- 
/** 
 * Ctor
 * 
 * @param damping
 * @param springConstant
 * @param maxVel
 */
VelocityController::VelocityController(float damping, float springConstant, float maxVel)
: m_fDamping(damping), m_fSpringConstant(springConstant), m_fMaxVelocity(maxVel)
{

}
//--------------------------------------------------------------------------------------------
/** 
 * Dtor
 * 
 */
VelocityController::~VelocityController()
{
}
//--------------------------------------------------------------------------------------------
/** 
 * Updates a certain velocity given a desired velocity
 * 
 * @param currentVel
 * @param desiredVel
 */
void VelocityController::Update(NiPoint3 &currentVel, const NiPoint3 &desiredVel)
{
	// generate force
	NiPoint3 force  = -m_fSpringConstant * (desiredVel - currentVel) + m_fDamping*currentVel; 
	// finds new velocity
	NiPoint3 newVel =  currentVel - force*0.1;

	// check if new velocity exceeds certain limits and constrain it
	// if needed
	float newVelLength = newVel.Length();

	if (newVelLength < -m_fMaxVelocity)
	{
		NiPoint3 heading = newVel;
		heading.Unitize();	
		newVel = -m_fMaxVelocity*heading;
	}
	else if (newVelLength > m_fMaxVelocity)
	{
		NiPoint3 heading = newVel;
		heading.Unitize();	
		newVel = m_fMaxVelocity*heading;
	}

	// set old velocity to new velocity
	currentVel = newVel;
}
//--------------------------------------------------------------------------------------------