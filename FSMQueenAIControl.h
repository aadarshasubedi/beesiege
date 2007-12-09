#ifndef FSMQUEENAICONTROL_H
#define FSMQUEENAICONTROL_H

#include "FSMAIControl.h"

class Queen;
class Flower;
class ConfigurationManager;

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

	Flower* m_pCurrentFlowerTarget;
	
private:

	// frame count
	int m_iFrames;
	// pointer to ConfigurationManager
	ConfigurationManager* m_pConfigManager;
	// radius to look for flowers
	const float m_fcFlowersRadius;

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

	// target closest flower bed
	void TargetClosestFlowers();

};

NiSmartPointer(FSMQueenAIControl);

#endif