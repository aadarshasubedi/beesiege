#ifndef FSMENEMYAICONTROL_H
#define FSMENEMYAICONTROL_H

#include "FSMAIControl.h"
#include "Locust.h"
#include "FSMEnemyMachine.h"

using namespace std;

class FSMEnemyAIControl: public FSMAIControl
{
public:
	FSMEnemyAIControl(Locust* locust);
	
	GameObj* m_TargetBee;
	bool isHealthBelowZero; //should be set in the UpdatePerceptions method
	bool isTargetDead;
	GameObj* m_queenBee;

	float m_nearestBeeDist;
	float m_distFromQueen;
	NiPoint3 m_collidePt;
	bool m_willCollide;
	float m_safetyRadius;

	void Update(int t);
	void UpdatePerceptions(int t);
	void Init();

	FSMEnemyMachine* m_enemy_machine;
	Locust* m_enemy;
};

NiSmartPointer(FSMEnemyAIControl);

#endif
