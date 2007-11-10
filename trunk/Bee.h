#ifndef BEE_H
#define BEE_H

#include "GameCharacter.h"
#include "Sound.h"

class Bee : public GameCharacter
{
public:
	Bee();
	~Bee();

	void Attack (GameCharacterPtr target);
	const bool WasAttackCommandIssued() const {return m_bAttackCommandIssued;}
	void ResetAttackCommand() { m_bAttackCommandIssued = false; }
private:

	void DoExtraUpdates(float fTime);
	bool DoExtraInits();
	SoundPtr m_spSound;
	bool m_bAttackCommandIssued;
};

NiSmartPointer(Bee);

#endif