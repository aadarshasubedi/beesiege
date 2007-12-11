/**
*	Base class for game character attributes
*/

#include "CharacterAttribute.h"
#include "GameCharacter.h"

//---------------------------------------------------------------------------------
NiImplementRTTI(CharacterAttribute,GameObj);
//---------------------------------------------------------------------------------
/**
*	Ctor
*   @param The owner of the attribute
*/
CharacterAttribute::CharacterAttribute(GameCharacter* owner)
: m_pOwner(owner)
{
}
//---------------------------------------------------------------------------------
/**
* Dtor
*/
CharacterAttribute::~CharacterAttribute()
{

}
//---------------------------------------------------------------------------------
