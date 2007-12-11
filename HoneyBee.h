#ifndef HONEYBEE_H
#define HONEYBEE_H

#include "GameCharacter.h"

class Flower;
class GameManager;

class HoneyBee : public GameCharacter
{
	NiDeclareRTTI;
public:
	HoneyBee();
	~HoneyBee();

	void GiveHoneyToQueen();

	const bool WasGatherIssued() const
	{
		return m_bIsGatherIssued;
	}
	void SetGather(Flower* target, bool value=true)
	{
		m_pTargetFlower = target;
		m_bIsGatherIssued = value;
	}
	Flower* GetFlowerTarget() const
	{
		return m_pTargetFlower;
	}
	const float GetGatheredHoney() const
	{
		return m_fHoneyGathered;
	}
	const bool HasHoney() const
	{
		return m_fHoneyGathered > 0.0f;
	}
	void IncreaseGatheredHoney(float value)
	{
		m_fHoneyGathered += value;
	}
	void ResetGatheredHoney()
	{
		m_fHoneyGathered = 0.0f;
	}

	
private:

	// extra updates and initializations
	void DoExtraUpdates(float fTime);
	bool DoExtraInits();
	
	bool m_bIsGatherIssued;
	Flower* m_pTargetFlower;

	float m_fHoneyGathered;

	GameManager* m_pGameManager;
};

NiSmartPointer(HoneyBee);

#endif