#ifndef QUEEN_H
#define QUEEN_H

#include "GameCharacter.h"
#include "Agent.h"


class Queen : public GameCharacter
{
public:
	Queen();
	~Queen();

	void MoveForward();
	void MoveBack();
	void StrafeLeft();
	void StrafeRight();
	void Rotate(float dx, float dy);

private:

	void DoExtraUpdates(float fTime);
	bool DoExtraInits();
};

NiSmartPointer(Queen);

#endif