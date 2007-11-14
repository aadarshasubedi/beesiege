#ifndef AGENT_H_
#define AGENT_H_

#include "GameObj.h"
#include <NiPoint3.h>
#include "CharacterController.h"
#include <NxVec3.h>

class NxActor;


class Agent : public GameObj
{
public:

	Agent(NxActor* actor);
	virtual ~Agent();
	void Update();
	void LookAt (const NxVec3& target);
	
	void SetTarget (NxActor* target)
	{
		m_pTarget = target;
	}
	NxActor* GetTarget() const
	{
		return m_pTarget;
	}
	void SetTarget (const NxVec3& target)
	{
		m_vTargetPosition = target;
	}
	const NxVec3 GetTargetPosition() const
	{
		return m_vTargetPosition;
	}
	CharacterControllerPtr GetController() const { return m_spController; }
	NxActor* GetActor() const { return m_pActor; }
	
protected:

	NxActor*    m_pActor;
	NxActor*    m_pTarget;
	NxVec3      m_vTargetPosition;
	CharacterControllerPtr m_spController;

};

NiSmartPointer(Agent);
#endif