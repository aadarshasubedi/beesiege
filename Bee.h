#ifndef BEE_H
#define BEE_H

#include "GameCharacter.h"
#include "Agent.h"
#include "Arrival.h"
#include "Separation.h"

class Bee : public GameCharacter
{
public:
	Bee();
	~Bee();
private:

	void DoExtraUpdates(float fTime);
	bool DoExtraInits();
	ArrivalPtr m_spArrival;
	SeparationPtr m_spSep;
};

NiSmartPointer(Bee);

#endif