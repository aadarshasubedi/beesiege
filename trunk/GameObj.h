#ifndef GAMEOBJ_H
#define GAMEOBJ_H


#include <NiObject.h>
#include <NiSmartPointer.h>

#pragma warning(disable: 4018)

class GameObj : public NiObject
{
	NiDeclareRTTI;
public:
	GameObj(){};
	virtual ~GameObj(){}

};

NiImplementRTTI(GameObj, NiObject);

NiSmartPointer(GameObj);

#endif