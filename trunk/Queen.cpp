#include "Queen.h"
#include "ConfigurationManager.h"
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
	m_spAgent->GetActor()->addForce(heading*ConfigurationManager::Get()->queen_speedGain);
}
//------------------------------------------------------------------------
void Queen::MoveBack()
{
	NxMat33 rotation = m_spAgent->GetActor()->getGlobalOrientation();
	NxVec3 heading = rotation.getColumn(0);
	m_spAgent->GetActor()->addForce(-heading*ConfigurationManager::Get()->queen_speedGain);
}
//------------------------------------------------------------------------
void Queen::StrafeLeft()
{
	NxMat33 rotation = m_spAgent->GetActor()->getGlobalOrientation();
	NxVec3 z = rotation.getColumn(2);
	m_spAgent->GetActor()->addForce(-z*ConfigurationManager::Get()->queen_speedGain);
}
//------------------------------------------------------------------------
void Queen::StrafeRight()
{
	NxMat33 rotation = m_spAgent->GetActor()->getGlobalOrientation();
	NxVec3 z = rotation.getColumn(2);
	m_spAgent->GetActor()->addForce(z*ConfigurationManager::Get()->queen_speedGain);
}
//------------------------------------------------------------------------
void Queen::Rotate(float dx, float dy)
{
	float rotationGain = ConfigurationManager::Get()->queen_rotationGain;
	m_spAgent->GetActor()->addLocalTorque(NxVec3(0.0, -dx*rotationGain, -dy*rotationGain));
}
//------------------------------------------------------------------------
