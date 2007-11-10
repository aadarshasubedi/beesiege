#ifndef FSMENEMYAICONTROL_H
#define FSMENEMYAICONTROL_H

#include "FSMAIControl.h"
#include "Locust.h"
#include "FSMMachine.h"

using namespace std;

class FSMEnemyAIControl: public FSMAIControl
{
public:
	FSMEnemyAIControl(GameCharacter* enemy);
	
	GameObj* m_TargetBee;
	bool isHealthBelowZero; //should be set in the UpdatePerceptions method
	bool isTargetDead;
	GameObj* m_queenBee;

	float m_distFromQueen;
	float m_health;
	
	void UpdatePerceptions(int t);
	void Init();

private:
	void DoExtraUpdates(float t){}
};

NiSmartPointer(FSMEnemyAIControl);

#endif
