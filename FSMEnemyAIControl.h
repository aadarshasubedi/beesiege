#ifndef FSMENEMYAICONTROL_H
#define FSMENEMYAICONTROL_H

#include "FSMAIControl.h"

class Enemy;
class GameCharacter;

class FSMEnemyAIControl: public FSMAIControl
{
	NiDeclareRTTI;
public:
	FSMEnemyAIControl(Enemy* enemy);
	~FSMEnemyAIControl();

	// is a target close by
	GameCharacter* IsTargetAtProximity(float radius);
	// is a bee close by
	GameCharacter* IsBeeAtProximity(float radius);
	// play sound when dying
	void PlayDyingSound();

private:
	// see base class
	void UpdatePerceptions(float fTime);
	void DoExtraUpdates(float fTime);
	
};

NiSmartPointer(FSMEnemyAIControl);

#endif
