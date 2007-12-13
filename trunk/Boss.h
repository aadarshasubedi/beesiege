#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

class Boss : public Enemy
{
	NiDeclareRTTI;
public:
	Boss();
	~Boss();

private:

	// extra updates and initializations
	void DoExtraUpdates(float fTime);
	bool DoExtraInits();

};

NiSmartPointer(Boss);

#endif