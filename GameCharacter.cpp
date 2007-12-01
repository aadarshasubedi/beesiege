/**
 * A GameCharacter. Inherits from GameObj3d
 */

#include "GameCharacter.h"
#include "GameManager.h"
#include "FSMAIControl.h"
#include "HealthAttribute.h"

//----------------------------------------------------------------------
// implements RTTI
NiImplementRTTI(GameCharacter, GameObj3d);
//------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 * @param type
 */
GameCharacter::GameCharacter(ResourceManager::ResourceType type) : GameObj3d(type),																								   
																   m_pActor(0)
{
}
//------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
GameCharacter::~GameCharacter()
{
	m_tAttributes.RemoveAll();
	healthBill = 0;
}
//------------------------------------------------------------------------ 
/** 
 * Do extra updates
 */
void GameCharacter::DoExtraUpdates(float fTime)
{
	AttributeType type;
	CharacterAttributePtr attr;
	NiTMapIterator it = m_tAttributes.GetFirstPos();
	for (int i=0; i<m_tAttributes.GetCount(); i++)
	{
		m_tAttributes.GetNext(it, type, attr);
		if (attr) attr->Update(fTime);
	}

	NxVec3 p = m_pActor->getGlobalPosition();
	healthBill->SetTranslate(p.x, p.y + 2.0f, p.z);
	HealthAttribute* h = ((HealthAttribute*)GetAttribute(GameCharacter::ATTR_HEALTH));
	if (h)
	{
		float health = h->GetHealth();
		SetEmmitanceForNode((NiAVObject*)healthBill, NiColor(1.0 - health/10.0f,health/10.0f,0.0));
	}
}
//------------------------------------------------------------------------ 
/** 
 * Do extra initializations
 * 
 * 
 * @return bool
 */
bool GameCharacter::DoExtraInits()
{
	// get actor
	NxActor* myactor = m_spProp->GetSnapshot()->GetActorAt(0)->GetActor();
	if (!myactor)
	{
		return false;
	}

	// set dampings
	myactor->setLinearDamping(5.0f);
	myactor->setAngularDamping(5.0f);
	
	//m_spAgent = NiNew Agent(myactor);
	m_pActor = myactor;

	healthBill = ResourceManager::Get()->GetNode(ResourceManager::RES_MODEL_HEALTH);
	GameManager::Get()->GetGameApp()->GetScene()->AttachChild(healthBill);
	NxVec3 p = m_pActor->getGlobalPosition();
	healthBill->SetTranslate(p.x, p.y + 5.0f, p.z);

	return true;
}
//------------------------------------------------------------------------ 
/** 
 * Gets an attribute of a given type
 * @return attribute
 */
CharacterAttribute* GameCharacter::GetAttribute(AttributeType type)
{
	if (m_tAttributes.IsEmpty()) return 0;
	CharacterAttributePtr attr = 0;
	m_tAttributes.GetAt(type, attr);
	return attr;
}