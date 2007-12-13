#ifndef QUEEN_H
#define QUEEN_H

#include "Enemy.h"
#include "Bee.h"
#include "HealerBee.h"
#include "HoneyBee.h"
#include <NiTPointerList.h>


class Queen : public GameCharacter
{
	NiDeclareRTTI;

public:
	Queen();
	~Queen();

	// adds / removes a soldier from the queen's list
	void AddSoldier (BeePtr soldier);
	void RemoveSoldier (BeePtr soldier);
	// adds / removes a healer from the queen's list
	void AddHealer (HealerBeePtr healer);
	void RemoveHealer (HealerBeePtr healer);
	// adds / removes a gatherer from the queen's list
	void AddGatherer (HoneyBeePtr gatherer);
	void RemoveGatherer (HoneyBeePtr gatherer);

	// reset queen
	void Reset();

	// getters / setters
	const NiTPointerList<BeePtr>& GetSoldiers() const
	{
		return m_lSoldiers;
	}
	const NiTPointerList<HealerBeePtr>& GetHealers() const
	{
		return m_lHealers;
	}
	const NiTPointerList<HoneyBeePtr>& GetGatherers() const
	{
		return m_lGatherers;
	}

	const bool WasSelectSoldiersIssued() const
	{
		return m_bIssuedSelectSoldiers;
	}

	const bool WasSelectGatherersIssued() const
	{
		return m_bIssuedSelectGatherers;
	}

	const bool WasAttackEnemyIssued() const
	{
		return m_bIssuedAttackEnemy;
	}

	const bool WasGatherIssued() const
	{
		return m_bIssuedGather;
	}

	const bool WasTargetEnemyIssued() const
	{
		return m_bIssuedTargetEnemy;
	}

	const bool WasMoveForwardIssued() const
	{
		return m_bIssuedMoveForward;
	}

	const bool WasMoveBackwardIssued() const
	{
		return m_bIssuedMoveBackward;
	}

	const bool WasMoveLeftIssued() const
	{
		return m_bIssuedMoveLeft;
	}

	const bool WasMoveRightIssued() const
	{
		return m_bIssuedMoveRight;
	}

	const bool WasMoveVerticalIssued() const
	{
		return m_bIssuedMoveVertical;
	}

	const bool WasRotateIssued() const
	{
		return m_bIssuedRotate;
	}

	void SetSelectSoldiers(bool value=true)
	{
		m_bIssuedSelectSoldiers = value;
	}

	void SetSelectGatherers(bool value=true)
	{
		m_bIssuedSelectGatherers = value;
	}

	void SetAttackEnemy(bool value=true)
	{
		m_bIssuedAttackEnemy = value;
	}

	void SetGather(bool value=true)
	{
		m_bIssuedGather = value;
	}

	void SetTargetEnemy(bool value=true)
	{
		m_bIssuedTargetEnemy = value;
	}

	void SetMoveForward(bool value=true)
	{
		m_bIssuedMoveForward = value;
	}

	void SetMoveBackward(bool value=true)
	{
		m_bIssuedMoveBackward = value;
	}

	void SetMoveLeft(bool value=true)
	{
		m_bIssuedMoveLeft = value;
	}

	void SetMoveRight(bool value=true)
	{
		m_bIssuedMoveRight = value;
	}

	void SetMoveVertical(float dy, bool value=true)
	{
		m_bIssuedMoveVertical = value;
		m_fRotateDy = dy;
	}

	void SetRotate(float dx, bool value=true)
	{
		m_bIssuedRotate = value;
		m_fRotateDx = dx;
		
	}

	const float GetRotateDx() const
	{
		return m_fRotateDx;
	}

	const float GetRotateDy() const
	{
		return m_fRotateDy;
	}

	void IncreaseHoney (float amount)
	{
		m_fHoney += amount;
	}

	void DecreaseHoney (float amount)
	{
		m_fHoney -= amount;
		if (m_fHoney < 0.0f)
		{
			m_fHoney = 0.0f;
		}
	}

	const bool HasHoney() const
	{
		return m_fHoney > 0.0f;
	}

	const float GetHoney() const
	{
		return m_fHoney;
	}
private:

	// extra updates and initializations
	void DoExtraUpdates(float fTime);
	bool DoExtraInits();

	// was select soldiers command issued
	bool m_bIssuedSelectSoldiers;
	// was select gatherers command issued
	bool m_bIssuedSelectGatherers;
	// was attack command issued
	bool m_bIssuedAttackEnemy;
	// was gather command issued
	bool m_bIssuedGather;
	// was target enemy command issued
	bool m_bIssuedTargetEnemy;
	// was move command issued
	bool m_bIssuedMoveForward;
	bool m_bIssuedMoveBackward;
	bool m_bIssuedMoveLeft;
	bool m_bIssuedMoveRight;
	bool m_bIssuedMoveVertical;
	// was rotate command issued
	bool m_bIssuedRotate;
	// a list that contains the queen's soldiers
	NiTPointerList<BeePtr> m_lSoldiers;
	// a list that contains the queen's healers
	NiTPointerList<HealerBeePtr> m_lHealers;
	// a list that contains the queen's honey bees
	NiTPointerList<HoneyBeePtr> m_lGatherers;
	// amount of rotation to be added
	float				   m_fRotateDx;
	float				   m_fRotateDy;

	// amount of honey available to create bees
	float m_fHoney;
};

NiSmartPointer(Queen);

#endif