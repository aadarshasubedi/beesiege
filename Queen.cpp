#include "Queen.h"

//------------------------------------------------------------------------
Queen::Queen() : GameCharacter(ResourceManager::RES_MODEL_QUEEN)		 
{
	
}
//------------------------------------------------------------------------
Queen::~Queen()
{
	
}
//------------------------------------------------------------------------
void Queen::DoExtraUpdates(float fTime)
{
	
}
//------------------------------------------------------------------------
bool Queen::DoExtraInits()
{
	if (!GameCharacter::DoExtraInits())
	{
		return false;
	}

	return true;
}
//------------------------------------------------------------------------
void Queen::MoveForward()
{
	NxMat33 rotation = m_spAgent->GetActor()->getGlobalOrientation();
	NxVec3 heading = rotation.getColumn(0);
	m_spAgent->GetActor()->addForce(heading*1000.0f);
}
//------------------------------------------------------------------------
void Queen::MoveBack()
{
	NxMat33 rotation = m_spAgent->GetActor()->getGlobalOrientation();
	NxVec3 heading = rotation.getColumn(0);
	m_spAgent->GetActor()->addForce(-heading*1000.0f);
}
//------------------------------------------------------------------------
void Queen::StrafeLeft()
{
	NxMat33 rotation = m_spAgent->GetActor()->getGlobalOrientation();
	NxVec3 z = rotation.getColumn(2);
	m_spAgent->GetActor()->addForce(-z*1000.0f);
}
//------------------------------------------------------------------------
void Queen::StrafeRight()
{
	NxMat33 rotation = m_spAgent->GetActor()->getGlobalOrientation();
	NxVec3 z = rotation.getColumn(2);
	m_spAgent->GetActor()->addForce(z*1000.0f);
}
//------------------------------------------------------------------------
void Queen::Rotate(float dx, float dy)
{
	
	m_spAgent->GetActor()->addLocalTorque(NxVec3(0.0, -dx*500.0f, -dy*500.0f));
}
//------------------------------------------------------------------------
