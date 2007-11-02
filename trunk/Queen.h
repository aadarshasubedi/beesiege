#ifndef QUEEN_H
#define QUEEN_H

#include "GameCharacter.h"
#include "Bee.h"
#include <NiTPointerList.h>

class CharacterDistancePair : public GameObj
{
	friend class Queen;
private: 
	CharacterDistancePair(float d, GameCharacterPtr c) : 
	   distance(d), character(c)
	   {}
	~CharacterDistancePair()
	{
		character = 0;
	}

	float distance;
	GameCharacterPtr character;
};

NiSmartPointer(CharacterDistancePair);

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

	void AddSoldier(BeePtr soldier);
	void CycleTarget(const NiTPointerList<GameCharacterPtr>& enemies);
	void SelectMoreSoldiers();
	void StopSelectingSoldiers();

private:

	void DoExtraUpdates(float fTime);
	bool DoExtraInits();
	//void MergeSort(NiTPointerList<CharacterDistancePairPtr>& unsorted, 
	//				  NiTPointerList<CharacterDistancePairPtr>& sorted)
	//void SortSoldiers(const NxVec3& target, NiTPointerList<CharacterDistancePairPtr>& sorted);
	//void SendSoldiers(const NxVec3& target, NiTPointerList<CharacterDistancePairPtr>& sorted);
	//void SelectSoldiersClosestTo (const NxVec3& target, unsigned int count);
	BeePtr FindSoldierClosestTo (const NxVec3& target);


	NiTPointerList<BeePtr>					 m_lSoldiers;
	NiTPointerList<BeePtr>					 m_lSelectedSoldiers;
	NiTListIterator							 m_itCurrentTargetPosition;
	GameCharacterPtr						 m_spCurrentTarget;
	const float								 m_fcQueenViewRadius;
	float									 m_fSelectionTimer;
	const float                              m_fcFogDefaultDepth;
	const float                              m_fcMaxHeight;
	const float                              m_fcFogScaleValue;
};

NiSmartPointer(Queen);

#endif