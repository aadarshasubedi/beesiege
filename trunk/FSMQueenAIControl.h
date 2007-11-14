#ifndef FSMQUEENAICONTROL_H
#define FSMQUEENAICONTROL_H

#include "FSMAIControl.h"

class Queen;

class FSMQueenAIControl: public FSMAIControl
{
public:
	FSMQueenAIControl(Queen* queen);
	~FSMQueenAIControl();

	bool issuedTargetEnemyCommand;
	bool issuedSelectSoldiersCommand;
	bool issuedAttackCommand;
	bool issuedMoveForwardCommand;
	bool issuedMoveBackwardCommand;
	bool issuedMoveLeftCommand;
	bool issuedMoveRightCommand;
	bool issuedMoveVerticalCommand;
	bool issuedRotateCommand;
	
private:

	void DoExtraUpdates(float fTime);
	void UpdatePerceptions(float fTime);

	void MoveQueenForward();
	void MoveQueenBackward();
	void MoveQueenLeft();
	void MoveQueenRight();
	void MoveQueenVertical();
	void RotateQueen();

};

NiSmartPointer(FSMQueenAIControl);

#endif