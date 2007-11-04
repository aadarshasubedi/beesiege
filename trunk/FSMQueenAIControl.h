#ifndef FSMQUEENAICONTROL_H
#define FSMQUEENAICONTROL_H

#include "FSMAIControl.h"
#include "Queen.h"
#include "FSMQueenMachine.h"

using namespace std;

class FSMQueenAIControl: public FSMAIControl
{
public:
	FSMQueenAIControl(Queen* queen);
	
	bool issuedPowerUpCommand;
	bool isHealthBelowZero;
	bool isHealthFull;

	bool isPowerUpEmpty;
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

	FSMQueenMachine* m_queen_machine;
	Queen* m_queen;
};

NiSmartPointer(FSMQueenAIControl);

#endif