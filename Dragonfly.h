#ifndef DRAGONFLY_H
#define DRAGONFLY_H

#include "Enemy.h"

class DragonFly : public Enemy
{
	NiDeclareRTTI;
public:
	DragonFly();
	~DragonFly();

private:

	// extra updates and initializations
	void DoExtraUpdates(float fTime);
	bool DoExtraInits();


};

NiSmartPointer(DragonFly);

#endif