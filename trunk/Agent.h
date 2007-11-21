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

	// ctor
	Agent(NxActor* actor);
	// dtor
	virtual ~Agent();
	// updates agent
	void Update();
	// rotates actor to look at a certain target
	void LookAt (const NxVec3& target);

	// getters, setters
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

	// the PhysX actor that is controlled
	NxActor*    m_pActor;
	// the actor's target
	NxActor*    m_pTarget;
	// the target's position
	NxVec3      m_vTargetPosition;
	// the controller that moves the actor
	CharacterControllerPtr m_spController;

};

NiSmartPointer(Agent);

#endif