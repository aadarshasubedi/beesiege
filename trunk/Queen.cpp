#include "Queen.h"
#include "ConfigurationManager.h"
#include <math.h>
#include "GameManager.h"
#include <NiMaterialProperty.h>
#include <stdio.h>
#include "TextManager.h"
//------------------------------------------------------------------------
Queen::Queen() : GameCharacter(ResourceManager::RES_MODEL_QUEEN), 
                 m_itCurrentTargetPosition(0),
				 m_spCurrentTarget(0),
				 m_fcQueenViewRadius(ConfigurationManager::Get()->queen_viewRadius),
				 m_uiSelectedSoldiersCount(0),
				 m_fSelectionTimer(ConfigurationManager::Get()->timer_selectSoldiers)
{
	
}
//------------------------------------------------------------------------
Queen::~Queen()
{
	m_lSoldiers.RemoveAll();
	m_lSelectedSoldiers.RemoveAll();
	m_lSortedEnemies.RemoveAll();
	m_spCurrentTarget = 0;
}
//------------------------------------------------------------------------
void Queen::DoExtraUpdates(float fTime)
{
	NxMat33 rotation = m_spAgent->GetActor()->getGlobalOrientation();
	rotation.setColumn(1, NxVec3(0.0, 1.0, 0.0));
	m_spAgent->GetActor()->setGlobalOrientation(rotation);
	NxVec3 nxHeading = rotation.getColumn(0);
	NxVec3 nxTarget = m_spAgent->GetActor()->getGlobalPosition() 
		- nxHeading*ConfigurationManager::Get()->bee_distanceFromTarget;
	
	NiTListIterator it = m_lSoldiers.GetHeadPos();
	for (unsigned int i=0; i<m_lSoldiers.GetSize(); i++)
	{
 		BeePtr soldier = m_lSoldiers.Get(it);
		soldier->SetTarget(nxTarget);
		it = m_lSoldiers.GetNextPos(it);
	}

	if (m_spCurrentTarget)
	{
		NxVec3 distance = m_spCurrentTarget->GetAgent()->GetActor()->getGlobalPosition() - 
			m_spAgent->GetActor()->getGlobalPosition();
		if (distance.magnitude() > m_fcQueenViewRadius)
		{
			m_spCurrentTarget->SetEmmitance(NiColor(0.0, 0.0, 0.0));
			m_spCurrentTarget = 0;
		}
	}
	
}
//------------------------------------------------------------------------
bool Queen::DoExtraInits()
{
	if (!GameCharacter::DoExtraInits())
	{
		return false;
	}

	GameManager::Get()->AddAgent(m_spAgent);

	return true;
}
//------------------------------------------------------------------------
void Queen::MoveForward()
{
	m_spAgent->GetActor()->addLocalForce(NxVec3(ConfigurationManager::Get()->queen_speedGain, 0.0, 0.0));
}
//------------------------------------------------------------------------
void Queen::MoveBack()
{
	m_spAgent->GetActor()->addLocalForce(NxVec3(-ConfigurationManager::Get()->queen_speedGain, 0.0, 0.0));
}
//------------------------------------------------------------------------
void Queen::StrafeLeft()
{
	m_spAgent->GetActor()->addLocalForce(NxVec3(0.0, 0.0, -ConfigurationManager::Get()->queen_speedGain));
}
//------------------------------------------------------------------------
void Queen::StrafeRight()
{
	m_spAgent->GetActor()->addLocalForce(NxVec3(0.0, 0.0, ConfigurationManager::Get()->queen_speedGain));
}
//------------------------------------------------------------------------
void Queen::Rotate(float dx, float dy)
{
	float rotationGain = ConfigurationManager::Get()->queen_rotationGain;
	m_spAgent->GetActor()->addLocalTorque(NxVec3(0.0, -dx*rotationGain,0.0));
	m_spAgent->GetActor()->addLocalForce(NxVec3(0.0, -dy*200.0f, 0.0));
}
//------------------------------------------------------------------------
void Queen::AddSoldier(BeePtr soldier)
{
	m_lSoldiers.AddTail(soldier);
}
//------------------------------------------------------------------------
void Queen::CycleTarget(const NiTPointerList<GameCharacterPtr>& enemies)
{
	if (enemies.IsEmpty()) return;

	if (m_itCurrentTargetPosition)
	{
		if (enemies.Get(m_itCurrentTargetPosition))
		{
			if (m_itCurrentTargetPosition == enemies.GetTailPos())
			{
				m_itCurrentTargetPosition = enemies.GetHeadPos();
			}
			else
			{
				m_itCurrentTargetPosition = enemies.GetNextPos(m_itCurrentTargetPosition);
			}
		}
		else
		{
			m_itCurrentTargetPosition = enemies.GetHeadPos();
		}
	}
	else
	{
		m_itCurrentTargetPosition = enemies.GetHeadPos();
	}

	if (m_spCurrentTarget)
	{
		m_spCurrentTarget->SetEmmitance(NiColor(0.0, 0.0, 0.0));
		m_spCurrentTarget = 0;
	}
	
	while(true)
	{
		m_spCurrentTarget = enemies.Get(m_itCurrentTargetPosition);
		NxVec3 distance = m_spCurrentTarget->GetAgent()->GetActor()->getGlobalPosition() - 
			m_spAgent->GetActor()->getGlobalPosition();
		if (distance.magnitude() <= m_fcQueenViewRadius)
		{
			break;
		}
		else
		{
			if (m_itCurrentTargetPosition == enemies.GetTailPos())
			{
				break;
			}
			else
			{
				m_itCurrentTargetPosition = enemies.GetNextPos(m_itCurrentTargetPosition);
			}
		}
	}
	
	if (m_spCurrentTarget)
	{
		m_spCurrentTarget->SetEmmitance(NiColor(1.0, 0.0, 0.0));
	}

}
//------------------------------------------------------------------------
void Queen::SelectMoreSoldiers()
{
	if (m_uiSelectedSoldiersCount < m_lSoldiers.GetSize())
	{
		m_fSelectionTimer += GameManager::Get()->GetDeltaTime();
		if (m_fSelectionTimer < ConfigurationManager::Get()->timer_selectSoldiers)
			return;
		m_uiSelectedSoldiersCount++;
		char selected[10];
		sprintf_s(selected, "%d", m_uiSelectedSoldiersCount);
		TextManager::Get()->UpdateText(TextManager::STRING_SELECTEDSOLDIERS, selected);
		m_fSelectionTimer = 0.0f;
	}
}
//------------------------------------------------------------------------
void Queen::StopSelectingSoldiers()
{
	if (m_uiSelectedSoldiersCount > 0)
	{
		if (m_spCurrentTarget)
		{
			NxVec3 target = m_spCurrentTarget->GetAgent()->GetActor()->getGlobalPosition();
			SelectSoldiersClosestTo(target, m_uiSelectedSoldiersCount);
			SendSoldiers(target, m_lSelectedSoldiers);
		}
		else
		{
			NxVec3 target = m_spAgent->GetActor()->getGlobalPosition();
			SelectSoldiersClosestTo(target, m_uiSelectedSoldiersCount);
		}

		m_uiSelectedSoldiersCount = 0;
		TextManager::Get()->UpdateText(TextManager::STRING_SELECTEDSOLDIERS, "");
		m_fSelectionTimer = ConfigurationManager::Get()->timer_selectSoldiers;
	}
}
//------------------------------------------------------------------------
void Queen::MergeSort(NiTPointerList<CharacterDistancePairPtr>& unsorted, 
					  NiTPointerList<CharacterDistancePairPtr>& sorted)
{
	sorted.RemoveAll();
	int k=1;
	NiTListIterator p;
	NiTListIterator q;
	
	while(1)
	{
		int merges = 0;
		p = unsorted.GetHeadPos();
		while(p)
		{
			merges++;
			q = p;
			int psize = 0;
			for (int i=0; i<k; i++)
			{
				psize++;
				q = unsorted.GetNextPos(q);
				if (!q) break;
			}	

			int qsize = k;
			while (psize > 0 || (qsize > 0 && q))
			{
				if (!psize)
				{
					sorted.AddTail(unsorted.RemovePos(q));
					qsize--;
				}
				else if (!qsize || q == 0)
				{
					sorted.AddTail(unsorted.RemovePos(p));
					psize--;
				}
				else
				{
					float pf = unsorted.Get(p)->distance;
					float qf = unsorted.Get(q)->distance;
					if (pf > qf)
					{
						sorted.AddTail(unsorted.RemovePos(q));
						qsize--;
					}
					else
					{
						sorted.AddTail(unsorted.RemovePos(p));
						psize--;
					}
				}
			}

			p = q;
			
		}
		if (merges <= 1) return;

		k *= 2;

		CopyLists(sorted, unsorted);
		sorted.RemoveAll();
	}
}
//------------------------------------------------------------------------
template <class T>
void Queen::CopyLists (const NiTPointerList<T> &from, NiTPointerList<T> &to)
{
	to.RemoveAll();
	NiTListIterator it = from.GetHeadPos();
	for (unsigned int i=0; i<from.GetSize(); i++)
	{
		to.AddTail(from.Get(it));
		it = from.GetNextPos(it);
	}
}
//------------------------------------------------------------------------
void Queen::SortSoldiers(const NxVec3& target, NiTPointerList<CharacterDistancePairPtr>& sorted)
{
	NiTListIterator it = m_lSoldiers.GetHeadPos();
	NiTPointerList<CharacterDistancePairPtr> distances;
	
	while (true)
	{
		BeePtr soldier = m_lSoldiers.Get(it);
		NxVec3 distance = target - soldier->GetAgent()->GetActor()->getGlobalPosition();
		CharacterDistancePairPtr p = NiNew CharacterDistancePair(distance.magnitude(), (GameCharacter*)soldier);
		distances.AddTail(p);
		if (it == m_lSoldiers.GetTailPos())
		{
			break;
		}
		else
		{
			it = m_lSoldiers.GetNextPos(it);
		}
	}

	MergeSort(distances, sorted);
	distances.RemoveAll();
}
//------------------------------------------------------------------------
void Queen::SendSoldiers(const NxVec3& target, NiTPointerList<CharacterDistancePairPtr>& sorted)
{
	NiTListIterator it = sorted.GetHeadPos();
	int size = sorted.GetSize();
	for (int i=0; i<size; i++)
	{
		BeePtr soldier = (Bee*)(GameCharacter*)sorted.Get(it)->character;
		soldier->SetTarget(target);
		m_lSoldiers.Remove(soldier);
		sorted.RemovePos(it);
	}
}
//------------------------------------------------------------------------
void Queen::SelectSoldiersClosestTo (const NxVec3& target, unsigned int count)
{
	if (m_lSoldiers.GetSize() == 1)
	{
		m_lSoldiers.GetHead()->SetTarget(target);
		m_lSoldiers.GetHead()->SetEmmitance(NiColor(0.0, 1.0, 0.0));
		m_lSoldiers.RemoveHead();
		return;
	}

	SortSoldiers(target, m_lSelectedSoldiers);
	NiTListIterator it = m_lSelectedSoldiers.GetHeadPos();
	for (int i=0; i<count; i++)
	{
		BeePtr soldier = (Bee*)(GameCharacter*)m_lSelectedSoldiers.Get(it)->character;
		soldier->SetEmmitance(NiColor(0.0, 1.0, 0.0));
		if (it != m_lSelectedSoldiers.GetTailPos())
		{
			it = m_lSelectedSoldiers.GetNextPos(it);
		}
	}
	int size = m_lSelectedSoldiers.GetSize();
	for (int i=count; i<size; i++)
	{
		m_lSelectedSoldiers.RemovePos(it);
	}
}