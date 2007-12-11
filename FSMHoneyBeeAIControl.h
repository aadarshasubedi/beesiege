#ifndef FSMHONEYBEEAICONTROL_H
#define FSMHONEYBEEAICONTROL_H

#include "FSMAIControl.h"

class HoneyBee;

class FSMHoneyBeeAIControl: public FSMAIControl
{
	NiDeclareRTTI;
public:
	// ctor / dtor
	FSMHoneyBeeAIControl(HoneyBee* bee);
	~FSMHoneyBeeAIControl();

	
	bool issuedGatherCommand;

private:
	
	// see base class
	void UpdatePerceptions(float fTime);
	void DoExtraUpdates(float fTime);

};

NiSmartPointer(FSMHoneyBeeAIControl);

#endif