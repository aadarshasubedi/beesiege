#ifndef FSMQUEENAICONTROL_H
#define FSMQUEENAICONTROL_H

#include "FSMAIControl.h"
#include "Queen.h"

#define FULL_HEALTH 100.0

using namespace std;

class FSMQueenAIControl: public FSMAIControl
{
public:
	FSMQueenAIControl();
	
	bool issuedPowerUpCommand;
	bool isHealthBelowZero;
	bool isHealthFull;

	bool isPowerUpEmpty;
	GameObj* m_nearestEnemy;
	GameObj* m_nearestPowerUp;
	float m_health;
	
	void Update(int t);
	void UpdatePerceptions(int t);
	void Init();

private:
	void DoExtraUpdates(float t){}
};

NiSmartPointer(FSMQueenAIControl);

#endif