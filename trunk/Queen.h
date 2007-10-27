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
	void MergeSort(NiTPointerList<CharacterDistancePairPtr>& unsorted, 
					  NiTPointerList<CharacterDistancePairPtr>& sorted);
	template <class T>
	void CopyLists (const NiTPointerList<T> &from, NiTPointerList<T> &to);
	void SortSoldiers(const NxVec3& target, NiTPointerList<CharacterDistancePairPtr>& sorted);
	void SendSoldiers(const NxVec3& target, NiTPointerList<CharacterDistancePairPtr>& sorted);
	void SelectSoldiersClosestTo (const NxVec3& target, unsigned int count);


	NiTPointerList<BeePtr>					 m_lSoldiers;
	NiTPointerList<CharacterDistancePairPtr> m_lSelectedSoldiers;
	NiTPointerList<CharacterDistancePairPtr> m_lSortedEnemies;
	NiTListIterator							 m_itCurrentTargetPosition;
	GameCharacterPtr						 m_spCurrentTarget;
	const float								 m_fcQueenViewRadius;
	unsigned int							 m_uiSelectedSoldiersCount; 
	float									 m_fSelectionTimer;
};

NiSmartPointer(Queen);

#endif