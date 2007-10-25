#ifndef BEE_H
#define BEE_H

#include "GameCharacter.h"
#include "Agent.h"

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