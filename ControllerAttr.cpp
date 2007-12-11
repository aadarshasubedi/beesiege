/**
* A character controller base class. If a character has a controller
* then it is able to move around the scene. 
*/

#include "ControllerAttr.h"


//-----------------------------------------------------------------------
NiImplementRTTI(ControllerAttr,CharacterAttribute);
//-----------------------------------------------------------------------
/**
* Ctor
* @param The owner of the attribute
*/
ControllerAttr::ControllerAttr(GameCharacter* owner) : CharacterAttribute(owner)
{
}
//-----------------------------------------------------------------------
/**
* Dtor
* 
*/
ControllerAttr::~ControllerAttr()
{
}