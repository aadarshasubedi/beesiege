#ifndef FSMAICONTROL_H
#define FSMAICONTROL_H

#include "GameObj.h"
#include "FSM.h"
#include <NiPoint3.h>

class GameCharacter;
class FSMMachine;

class FSMAIControl: public GameObj
{
public:
	FSMAIControl(GameCharacter* character);
	virtual ~FSMAIControl();
	void Update(int t);
	
	virtual void UpdatePerceptions(int t);
	virtual void Init();

	GameCharacter* m_character;
	FSMMachine* m_machine;

	const float m_fcPowerUpScanDistance;

private:

	virtual void DoExtraUpdates(float t) = 0;
};

NiSmartPointer(FSMAIControl);

#endif


