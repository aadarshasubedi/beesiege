#ifndef FSMAICONTROL_H
#define FSMAICONTROL_H

#define POWERUP_SCAN_DIST 30.0f

#include "FSM.h"
#include <NiPoint3.h>
#include "GameCharacter.h"

using namespace std;

class FSMAIControl
{
public:
	FSMAIControl(){}
	FSMAIControl(GameCharacter* character);
	
	virtual void Update(int t);
	virtual void UpdatePerceptions(int t);
	virtual void Init();
};

#endif

