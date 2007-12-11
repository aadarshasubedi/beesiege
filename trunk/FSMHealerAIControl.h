#ifndef FSMHEALERAICONTROL_H
#define FSMHEALERAICONTROL_H

#include "FSMAIControl.h"

class HealerBee;

class FSMHealerAIControl: public FSMAIControl
{
	NiDeclareRTTI;
public:
	// ctor / dtor
	FSMHealerAIControl(HealerBee* bee);
	~FSMHealerAIControl();

private:
	
	// healing radius
	const float m_fcRadius;
	// healing duration
	const float m_fcDuration;
	// healing amount
	const float m_fcHealAmount;
	// healing timer
	float m_fTimer;

	// see base class
	void UpdatePerceptions(float fTime);
	void DoExtraUpdates(float fTime);

	// heal allies in a radius
	void Heal();

};

NiSmartPointer(FSMHealerAIControl);

#endif