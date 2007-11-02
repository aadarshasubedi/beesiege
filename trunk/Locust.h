#ifndef LOCUST_H
#define LOCUST_H

#include "GameCharacter.h"

class Locust : public GameCharacter
{
public:
	Locust();
	~Locust();

private:

	void DoExtraUpdates(float fTime);
	bool DoExtraInits();


};

NiSmartPointer(Locust);

#endif