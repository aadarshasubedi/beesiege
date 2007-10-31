#ifndef GAMEOBJ_H
#define GAMEOBJ_H


#include <NiRefObject.h>
#include <NiSmartPointer.h>

#pragma warning(disable: 4018)

class GameObj : public NiRefObject
{
	
public:
	GameObj(){};
	virtual ~GameObj(){}

};

NiSmartPointer(GameObj);

#endif