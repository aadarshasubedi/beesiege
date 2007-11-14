/**
 * A GameCharacter. Inherits from GameObj3d
 */

#include "GameCharacter.h"
#include "GameManager.h"
#include "FSMAIControl.h"


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