#ifndef FSMQUEENAICONTROL_H
#define FSMQUEENAICONTROL_H

#include "FSMAIControl.h"
#include "Queen.h"
#include "FSMQueenMachine.h"

using namespace std;

class FSMQueenAIControl: public FSMAIControl
{
	FSMQueenAIControl(Queen* queen);
	
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
	FSMQueenMachine* m_queen_machine;
	Queen* m_queen;
};

#endif