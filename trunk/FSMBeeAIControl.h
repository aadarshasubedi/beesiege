#ifndef FSMBEEAICONTROL_H
#define FSMBEEAICONTROL_H

#include "FSMAIControl.h"

class GameCharacter;
class Bee;

class FSMBeeAIControl: public FSMAIControl
{
public:
	FSMBeeAIControl(Bee* bee);
	
	GameCharacter* m_TargetEnemy;
	bool isHealthBelowZero; //should be set in the UpdatePerceptions method
	bool isTargetDead;
	bool issuedAttackCommand; //this should become false once the bee goes into attack state
	GameCharacter* m_queenBee;
	float m_health;
	GameObj* m_nearestPowerUp;

	void UpdatePerceptions(int t);
	void Init();

private:
	void DoExtraUpdates(float t){}
};

NiSmartPointer(FSMBeeAIControl);

#endif