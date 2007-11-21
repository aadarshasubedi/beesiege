#ifndef QUEEN_H
#define QUEEN_H

#include "Enemy.h"
#include "Bee.h"
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
	// getters / setters
	const NiTPointerList<BeePtr>& GetSoldiers() const
	{
		return m_lSoldiers;
	}

	const bool WasSelectSoldiersIssued() const
	{
		return m_bIssuedSelectSoldiers;
	}

	const bool WasAttackEnemyIssued() const
	{
		return m_bIssuedAttackEnemy;
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

	void SetAttackEnemy(bool value=true)
	{
		m_bIssuedAttackEnemy = value;
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
private:

	// extra updates and initializations
	void DoExtraUpdates(float fTime);
	bool DoExtraInits();

	// was select soldiers command issued
	bool m_bIssuedSelectSoldiers;
	// was attack command issued
	bool m_bIssuedAttackEnemy;
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
	// amount of rotation to be added
	float				   m_fRotateDx;
	float				   m_fRotateDy;
};

NiSmartPointer(Queen);

#endif