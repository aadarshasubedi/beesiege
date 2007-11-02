#ifndef FSMBEEAICONTROL_H
#define FSMBEEAICONTROL_H

#include "FSMAIControl.h"
#include "Bee.h"
#include "FSMBeeMachine.h"

using namespace std;

class FSMBeeAIControl: public FSMAIControl
{
	FSMBeeAIControl(Bee* bee);
		
	GameObj* m_nearestEnemy;
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

private:
	FSMBeeMachine* m_bee_machine;
	Bee* m_bee;
};

NiSmartPointer(FSMBeeAIControl);

#endif