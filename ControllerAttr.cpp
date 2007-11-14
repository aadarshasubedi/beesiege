/**
* A character controller base class. If a character has a controller
* then it is able to move around the scene. 
*/

#include "ControllerAttr.h"


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