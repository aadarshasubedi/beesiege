/**
* This is a flower class which keeps flowers randomly in the scene 
* so that they act as a source to generate honey for the honey bees.
*/

#include "Flower.h"
#include "GameManager.h"

//--------------------------------------------------------------
NiImplementRTTI(Flower, GameObj3d);
//--------------------------------------------------------------

/**
* Constructor
*/
Flower::Flower() :
GameObj3d(ResourceManager::RES_MODEL_FLOWER),
m_fcMaxHoney(100.0f),
m_fHoneyCapacity(m_fcMaxHoney),
m_fcResetTime(120.0f),
m_fResetTimer(m_fcResetTime),
m_pGameManager(GameManager::Get())
{
}
//--------------------------------------------------------------

/**
* Destructor
*/
Flower::~Flower()
{
}
//--------------------------------------------------------------

void Flower::DoExtraUpdates(float fTime)
{
	if (!HasHoney())
	{
		m_fResetTimer -= m_pGameManager->GetDeltaTime();
		if (m_fResetTimer <= 0.0f)
		{
			ResetHoney();
			m_fResetTimer = m_fcResetTime;
		}
	}
}

//--------------------------------------------------------------
bool Flower::DoExtraInits()
{
	return true;
}
