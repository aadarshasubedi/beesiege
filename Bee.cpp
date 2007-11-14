/**
 * A Bee or a queen's soldier. 
 */

#include "Bee.h"
#include "FSMBeeAIControl.h"
#include "Enemy.h"
#include "GameManager.h"
#include "HealthAttribute.h"
#include "NiTMap.h"


//----------------------------------------------------------------------
// implements RTTI
NiImplementRTTI(Bee, GameCharacter);
//------------------------------------------------------------------------
/** 
 * Ctor
 * 
 */
Bee::Bee() : GameCharacter(ResourceManager::RES_MODEL_BEE),
			 m_pEnemyTarget(0),
			 m_bIssuedAttackCommand(false)
{
}
//------------------------------------------------------------------------
/** 
 * Dtor
 * 
 */
Bee::~Bee()
{
	
}
//------------------------------------------------------------------------
/** 
 * Updates the bee
 * 
 * @param fTime
 */
void Bee::DoExtraUpdates(float fTime)
{
	if (!m_tAttributes.IsEmpty())
	{
		NiTMapIterator it = m_tAttributes.GetFirstPos();
		CharacterAttributePtr attr = 0;
		GameCharacter::AttributeType key;
		for (int i=0; i<m_tAttributes.GetCount(); i++)
		{
			m_tAttributes.GetNext(it, key, attr);
			if (attr)
			{
				attr->Update(fTime);
			}
		}
	}
}
//------------------------------------------------------------------------ 
/** 
 * Initializes the bee's attributes 
 * 
 * 
 * @return bool
 */
bool Bee::DoExtraInits()
{
	if (!GameCharacter::DoExtraInits())
	{
		return false;
	}

	AddAttribute(GameCharacter::ATTR_CONTROLLER, NiNew FSMBeeAIControl(this));
	HealthAttributePtr health = NiNew HealthAttribute(this);
	health->Reset(10.0f);
	AddAttribute(GameCharacter::ATTR_HEALTH, (CharacterAttribute*)health);

	m_pActor->setGlobalPosition(GameManager::Get()->
		GetQueen()->GetActor()->getGlobalPosition() - NxVec3(100.0, 0.0, 0.0));
	return true;
}