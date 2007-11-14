#ifndef FSMBEEAICONTROL_H
#define FSMBEEAICONTROL_H

#include "FSMAIControl.h"

class Bee;
class Enemy;

class FSMBeeAIControl: public FSMAIControl
{
public:
	FSMBeeAIControl(Bee* bee);
	~FSMBeeAIControl();

	Enemy* m_pTargetEnemy;

	bool isHealthBelowZero; 
	bool isTargetDead;
	bool issuedAttackCommand; 

private:

	void UpdatePerceptions(float fTime);
	void DoExtraUpdates(float fTime);
};

NiSmartPointer(FSMBeeAIControl);

#endif