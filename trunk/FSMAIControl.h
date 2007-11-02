#ifndef FSMAICONTROL_H
#define FSMAICONTROL_H

#define POWERUP_SCAN_DIST 30.0f

#include "FSM.h"
#include <NiPoint3.h>
#include "GameCharacter.h"
#include "FSMState.h"

using namespace std;

class FSMAIControl: public GameObj
{
public:
	FSMAIControl(){};
	FSMAIControl(GameCharacter* character) = 0;
	
	virtual void Update(int t) = 0;
	virtual void UpdatePerceptions(int t) = 0;
	virtual void Init() = 0;
};

NiSmartPointer(FSMAIControl);

#endif


