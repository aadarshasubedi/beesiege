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

	void AddSoldier (BeePtr soldier);
	void RemoveSoldier (BeePtr soldier);
	
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

	void DoExtraUpdates(float fTime);
	bool DoExtraInits();

	bool m_bIssuedSelectSoldiers;
	bool m_bIssuedAttackEnemy;
	bool m_bIssuedTargetEnemy;
	bool m_bIssuedMoveForward;
	bool m_bIssuedMoveBackward;
	bool m_bIssuedMoveLeft;
	bool m_bIssuedMoveRight;
	bool m_bIssuedMoveVertical;
	bool m_bIssuedRotate;

	NiTPointerList<BeePtr> m_lSoldiers;
	
	float				   m_fRotateDx;
	float				   m_fRotateDy;
};

NiSmartPointer(Queen);

#endif