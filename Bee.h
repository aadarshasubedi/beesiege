#ifndef BEE_H
#define BEE_H

#include "GameCharacter.h"

class Bee : public GameCharacter
{
public:
	Bee();
	~Bee();

private:

	void DoExtraUpdates(float fTime);
	bool DoExtraInits();

};

NiSmartPointer(Bee);

#endif