#ifndef LOCUST_H
#define LOCUST_H

#include "Enemy.h"

class Locust : public Enemy
{
	NiDeclareRTTI;
public:
	Locust();
	~Locust();

private:

	// extra updates and initializations
	void DoExtraUpdates(float fTime);
	bool DoExtraInits();


};

NiSmartPointer(Locust);

#endif