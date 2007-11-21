#ifndef BEE_H
#define BEE_H

#include "GameCharacter.h"

class Enemy;

class Bee : public GameCharacter
{
	NiDeclareRTTI;
public:
	Bee();
	~Bee();

	// issues an attack command for the current target
	void SetAttack(Enemy* target, bool value=true)
	{
		m_pEnemyTarget = target;
		m_bIssuedAttackCommand = value;
	}
	// getters
	const bool WasAttackIssued() const
	{
		return m_bIssuedAttackCommand;
	}
	Enemy* GetEnemyTarget() const 
	{
		return m_pEnemyTarget;
	}
private:

	// extra updates and initializations
	void DoExtraUpdates(float fTime);
	bool DoExtraInits();
	// was an attack command issued
	bool m_bIssuedAttackCommand;
	// the bee's current target
	Enemy* m_pEnemyTarget;
};

NiSmartPointer(Bee);

#endif