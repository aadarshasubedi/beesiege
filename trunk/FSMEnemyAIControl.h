#ifndef FSMENEMYAICONTROL_H
#define FSMENEMYAICONTROL_H

#include "FSMAIControl.h"

class Enemy;
class GameCharacter;

class FSMEnemyAIControl: public FSMAIControl
{
public:
	FSMEnemyAIControl(Enemy* enemy);
	~FSMEnemyAIControl();

	GameCharacter* IsTargetAtProximity(float radius);

private:
	// see base class
	void UpdatePerceptions(float fTime);
	void DoExtraUpdates(float fTime);
};

NiSmartPointer(FSMEnemyAIControl);

#endif
