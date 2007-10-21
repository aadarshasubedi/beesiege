#ifndef AGENT_H_
#define AGENT_H_

#include "GameObj.h"
#include <NiPoint3.h>
#include "CharacterController.h"

class NxActor;
class NxVec3;

class Agent : public GameObj
{
public:

	Agent(NxActor* actor);
	virtual ~Agent();
	void Update(const NiPoint3& target);
	inline CharacterControllerPtr GetController() const { return m_spController; }
	inline NxActor* GetActor() const { return m_pActor; }
protected:

	NxActor*    m_pActor;
	CharacterControllerPtr m_spController;

};

NiSmartPointer(Agent);
#endif