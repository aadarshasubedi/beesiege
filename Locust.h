#ifndef LOCUST_H
#define LOCUST_H

#include "Enemy.h"

class Locust : public Enemy
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