#ifndef FSMAICONTROL_H
#define FSMAICONTROL_H

#include "ControllerAttr.h"
#include "FSM.h"
#include <NiPoint3.h>
#include "FSMMachine.h"
#include "Agent.h"

class GameCharacter;

class FSMAIControl: public ControllerAttr
{
public:
	FSMAIControl(GameCharacter* character);
	virtual ~FSMAIControl();

	void Update(float fTime);

	AgentPtr GetAgent() const
	{
		return m_spAgent;
	}

	FSMMachinePtr GetMachine() const
	{
		return m_spMachine;
	}
protected:

	FSMMachinePtr m_spMachine;
	AgentPtr m_spAgent;

	virtual void UpdatePerceptions(float fTime) = 0;
	virtual void DoExtraUpdates(float fTime) = 0;
};

NiSmartPointer(FSMAIControl);

#endif


