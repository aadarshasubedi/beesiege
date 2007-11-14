#ifndef FSMENEMYAICONTROL_H
#define FSMENEMYAICONTROL_H

#include "FSMAIControl.h"

class Enemy;

class FSMEnemyAIControl: public FSMAIControl
{
public:
	FSMEnemyAIControl(Enemy* enemy);
	~FSMEnemyAIControl();


private:

	void UpdatePerceptions(float fTime);
	void DoExtraUpdates(float fTime);
};

NiSmartPointer(FSMEnemyAIControl);

#endif
