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
	
	GameObj* m_nearestBee;
	float m_nearestBeeDist;
	float m_distFromQueen;
	NiPoint3 m_collidePt;
	bool m_willCollide;
	float m_safetyRadius;

	void Update(int t);
	void UpdatePerceptions(int t);
	void Init();

private:
	FSMEnemyMachine* m_enemy_machine;
	Locust* m_enemy;
};

NiSmartPointer(FSMEnemyAIControl);

#endif
