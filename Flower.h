#ifndef FLOWER_H
#define FLOWER_H

#include "GameObj3d.h"  

class Flower : public GameObj3d
{
	NiDeclareRTTI;

public: 

	Flower();		
	virtual ~Flower();	

protected:

	virtual void DoExtraUpdates(float fTime);
	virtual bool DoExtraInits();

};

NiSmartPointer(Flower);

#endif
