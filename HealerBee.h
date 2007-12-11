#ifndef HEALERBEE_H
#define HEALERBEE_H

#include "GameCharacter.h"

class HealerBee : public GameCharacter
{
	NiDeclareRTTI;
public:
	HealerBee();
	~HealerBee();

private:

	// extra updates and initializations
	void DoExtraUpdates(float fTime);
	bool DoExtraInits();
	
};

NiSmartPointer(HealerBee);

#endif