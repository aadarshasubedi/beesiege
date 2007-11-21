#ifndef FSMQUEENAICONTROL_H
#define FSMQUEENAICONTROL_H

#include "FSMAIControl.h"

class Queen;

class FSMQueenAIControl: public FSMAIControl
{
public:
	FSMQueenAIControl(Queen* queen);
	~FSMQueenAIControl();

	// flags that hold information about the queen's
	// state
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

	// see base class
	void DoExtraUpdates(float fTime);
	void UpdatePerceptions(float fTime);

	// move, rotate functions
	void MoveQueenForward();
	void MoveQueenBackward();
	void MoveQueenLeft();
	void MoveQueenRight();
	void MoveQueenVertical();
	void RotateQueen();

};

NiSmartPointer(FSMQueenAIControl);

#endif