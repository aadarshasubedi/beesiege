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

	void SetAttack(Enemy* target, bool value=true)
	{
		m_pEnemyTarget = target;
		m_bIssuedAttackCommand = value;
	}
	const bool WasAttackIssued() const
	{
		return m_bIssuedAttackCommand;
	}
	Enemy* GetEnemyTarget() const 
	{
		return m_pEnemyTarget;
	}
private:

	void DoExtraUpdates(float fTime);
	bool DoExtraInits();
	
	bool m_bIssuedAttackCommand;
	Enemy* m_pEnemyTarget;
};

NiSmartPointer(Bee);

#endif