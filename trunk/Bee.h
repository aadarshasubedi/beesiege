#ifndef BEE_H
#define BEE_H

#include "GameCharacter.h"
#include "Sound.h"

class Bee : public GameCharacter
{
public:
	Bee();
	~Bee();

private:

	void DoExtraUpdates(float fTime);
	bool DoExtraInits();
	SoundPtr m_spSound;

};

NiSmartPointer(Bee);

#endif