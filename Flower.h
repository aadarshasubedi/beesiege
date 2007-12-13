#ifndef FLOWER_H
#define FLOWER_H

#include "GameObj3d.h"  

class GameManager;

class Flower : public GameObj3d
{
	NiDeclareRTTI;

public: 

	Flower();		
	~Flower();	

	const bool HasHoney() const
	{
		return m_fHoneyCapacity > 0.0f;
	}

	void DecreaseHoneyAmount (float value)
	{
		m_fHoneyCapacity -= value;
	}

	void ResetHoney()
	{
		m_fHoneyCapacity = m_fcMaxHoney;
	}

protected:

	void DoExtraUpdates(float fTime);
	bool DoExtraInits();
	

	// maxi honey capacity
	const float m_fcMaxHoney;
	// amount of honey
	float m_fHoneyCapacity;
	// timer to reset flower
	const float m_fcResetTime;
	float m_fResetTimer;
	// pointer to the game manager
	GameManager* m_pGameManager;

};

NiSmartPointer(Flower);

#endif
