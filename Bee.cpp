#include "Bee.h"
#include "GameManager.h"
#include "Wander.h"
#include "BehaviorCombo.h"
#include <list>
using namespace std;
//------------------------------------------------------------------------
Bee::Bee() : GameCharacter(ResourceManager::RES_MODEL_BEE)		 
{
}
//------------------------------------------------------------------------
Bee::~Bee()
{
	m_spArrival  = 0;
	m_spSep = 0;
}
//------------------------------------------------------------------------
void Bee::DoExtraUpdates(float fTime)
{
	NxActor* queenActor = GameManager::Get()->GetQueen()->GetAgent()->GetActor();
	NxMat33 rotation = queenActor->getGlobalOrientation();
	NxVec3 nxHeading = rotation.getColumn(0);
	NxVec3 nxTarget = queenActor->getGlobalPosition() - nxHeading*150.0f;
	NiPoint3 target(nxTarget.x, nxTarget.y, nxTarget.z);
	m_spAgent->Update(target);
}
//------------------------------------------------------------------------
bool Bee::DoExtraInits()
{
	if (!GameCharacter::DoExtraInits())
	{
		return false;
	}

	list<BehaviorPtr> vAWS;
	vAWS.push_back(NiNew Arrival());
	vAWS.push_back(NiNew Wander());
	vAWS.push_back(NiNew Separation());

	list<float> vAWSCoef;
	vAWSCoef.push_back(1.0f);
	vAWSCoef.push_back(0.5f);
	vAWSCoef.push_back(1.5f);

	BehaviorComboPtr aws = NiNew BehaviorCombo("", vAWS, vAWSCoef);
	m_spArrival = NiNew Arrival;
	m_spSep= NiNew Separation;
	m_spAgent->GetController()->SetBehavior((Behavior*)(BehaviorCombo*)aws);

	m_spAgent->GetActor()->setLinearDamping(7.0f);
	m_spAgent->GetActor()->setAngularDamping(10.0f);

	return true;
}