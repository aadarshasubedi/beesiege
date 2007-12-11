#ifndef FSMAICONTROL_H
#define FSMAICONTROL_H

#include "ControllerAttr.h"
#include "FSM.h"
#include <NiPoint3.h>
#include "FSMMachine.h"
#include "Agent.h"

class GameCharacter;
class GameManager;

class FSMAIControl: public ControllerAttr
{
	NiDeclareRTTI;
public:
	// ctor / dtor
	FSMAIControl(GameCharacter* character);
	virtual ~FSMAIControl();
	// updates the attribute
	void Update(float fTime);
	// getters
	AgentPtr GetAgent() const
	{
		return m_spAgent;
	}

	FSMMachinePtr GetMachine() const
	{
		return m_spMachine;
	}
protected:
	// the finite state machine associated with the
	// controller
	FSMMachinePtr m_spMachine;
	// the agent that the controller operates with
	AgentPtr m_spAgent;
	// pointer to the gamemanager
	GameManager* m_pGameManager;
	// collects information about the state of the environment
	virtual void UpdatePerceptions(float fTime) = 0;
	// performs extra updates
	virtual void DoExtraUpdates(float fTime) = 0;
};

NiSmartPointer(FSMAIControl);

#endif


