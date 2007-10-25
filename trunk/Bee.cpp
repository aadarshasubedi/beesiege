#include "Bee.h"
#include "GameManager.h"
#include "Wander.h"
#include "BehaviorCombo.h"
#include "ConfigurationManager.h"
#include "Arrival.h"
#include "Separation.h"

#include <list>
using namespace std;
//------------------------------------------------------------------------
Bee::Bee() : GameCharacter(ResourceManager::RES_MODEL_BEE)		 
{
}
//------------------------------------------------------------------------
Bee::~Bee()
{
	
}
//------------------------------------------------------------------------
void Bee::DoExtraUpdates(float fTime)
{
	NxActor* queenActor = GameManager::Get()->GetQueen()->GetAgent()->GetActor();
	NxMat33 rotation = queenActor->getGlobalOrientation();
	NxVec3 nxHeading = rotation.getColumn(0);
	NxVec3 nxTarget = queenActor->getGlobalPosition() - 
		nxHeading*ConfigurationManager::Get()->bee_distanceFromTarget;
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

	m_spAgent->GetController()->SetBehavior((Behavior*)aws);

	return true;
}