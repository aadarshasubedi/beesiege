#ifndef CONTROLLERATTR_H
#define CONTROLLERATTR_H

#include "CharacterAttribute.h"
#include "GameCharacter.h"

class ControllerAttr : public CharacterAttribute
{
public:

	ControllerAttr(GameCharacter* owner);
	virtual ~ControllerAttr();

	virtual void Update(float fTime) = 0;
};

NiSmartPointer(ControllerAttr);

#endif