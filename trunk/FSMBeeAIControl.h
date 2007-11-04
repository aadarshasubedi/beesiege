#ifndef FSMBEEAICONTROL_H
#define FSMBEEAICONTROL_H

#include "FSMAIControl.h"
#include "Bee.h"
#include "FSMBeeMachine.h"

using namespace std;

class FSMBeeAIControl: public FSMAIControl
{
public:
	FSMBeeAIControl(Bee* bee);

	GameObj* m_TargetEnemy;
	bool isHealthBelowZero; //should be set in the UpdatePerceptions method
	bool isTargetDead;
	bool issuedAttackCommand; //this should become false once the bee goes into attack state
	GameObj* m_queenBee;

	GameObj* m_nearestPowerUp;

	float m_nearestEnemyDist;
	float m_nearestPowerUpDist;
	NiPoint3 m_collidePt;
	bool m_willCollide;
	bool m_powerUpNear;
	float m_safetyRadius;

	void Update(int t);
	void UpdatePerceptions(int t);
	void Init();

	FSMBeeMachine* m_bee_machine;
	Bee* m_bee;
};

NiSmartPointer(FSMBeeAIControl);

#endif