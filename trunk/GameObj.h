#ifndef GAMEOBJ_H
#define GAMEOBJ_H


#include <NiObject.h>
#include <NiSmartPointer.h>

#pragma warning(disable: 4018)

class GameObj : public NiObject
{
	// declares RTTI for using NiIsKindOf(classname, object)
	NiDeclareRTTI;
public:
	// ctor / dtor
	GameObj(){};
	virtual ~GameObj(){}

};

NiImplementRTTI(GameObj, NiObject);

NiSmartPointer(GameObj);

#endif