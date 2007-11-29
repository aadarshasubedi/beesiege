#ifndef ENEMY_H
#define ENEMY_H

#include "GameCharacter.h"

class Enemy : public GameCharacter
{
	NiDeclareRTTI;
public:
	Enemy(ResourceManager::ResourceType type);
	virtual ~Enemy();

	void AddAttacker(GameCharacterPtr attacker, AgentPtr attackerAgent)
	{
		m_lAttackers.AddTail(attacker);
		m_lAttackerAgents.AddTail(attackerAgent);
	}

	const NiTPointerList<GameCharacterPtr>& GetAttackers() const
	{
		return m_lAttackers;
	}

	const NiTPointerList<AgentPtr>& GetAttackersAgents() const
	{
		return m_lAttackerAgents;
	}

	void SetStrongAttack (bool value)
	{
		m_bIsAttackStrong = value;
	}

	const bool IsAttackStrong() const
	{
		return m_bIsAttackStrong;
	}

protected:

	// extra updates and initializations
	virtual void DoExtraUpdates(float fTime) = 0;
	virtual bool DoExtraInits();

	NiTPointerList<GameCharacterPtr> m_lAttackers;
	NiTPointerList<AgentPtr> m_lAttackerAgents;

	// are the attackers cohesive
	bool m_bIsAttackStrong;

};

NiSmartPointer(Enemy);

#endif