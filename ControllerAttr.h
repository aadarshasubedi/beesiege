#ifndef CONTROLLERATTR_H
#define CONTROLLERATTR_H

#include "CharacterAttribute.h"
#include "GameCharacter.h"

class ControllerAttr : public CharacterAttribute
{

	NiDeclareRTTI;
public:
	// ctor / dtor
	ControllerAttr(GameCharacter* owner);
	virtual ~ControllerAttr();
	// pure virtual update
	virtual void Update(float fTime) = 0;
};

NiSmartPointer(ControllerAttr);

#endif