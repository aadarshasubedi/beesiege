#ifndef FSMBEEAICONTROL_H
#define FSMBEEAICONTROL_H

#include "FSMAIControl.h"

class Bee;
class Enemy;

class FSMBeeAIControl: public FSMAIControl
{
public:
	// ctor / dtor
	FSMBeeAIControl(Bee* bee);
	~FSMBeeAIControl();
	
	// play a sound when dying
	void PlayDyingSound();

	// the bee's target
	Enemy* m_pTargetEnemy;
	// booleans that affect the controller's states
	bool isHealthBelowZero; 
	bool isTargetDead;
	bool issuedAttackCommand; 


private:
	// see base class
	void UpdatePerceptions(float fTime);
	void DoExtraUpdates(float fTime);
};

NiSmartPointer(FSMBeeAIControl);

#endif