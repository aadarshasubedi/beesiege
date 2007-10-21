#ifndef GAMEOBJ_H
#define GAMEOBJ_H


#include <NiRefObject.h>
#include <NiSmartPointer.h>

class GameObj : public NiRefObject
{
	
public:
	GameObj(){};
	virtual ~GameObj(){}

};

NiSmartPointer(GameObj);

#endif