#include "BehaviorCollection.h"
#include "Seek.h"
#include "Flee.h"
#include "Arrival.h"
#include "Departure.h"
#include "Wander.h"
#include "Separation.h"
#include "Alignment.h"
#include "Cohesion.h"
#include "BehaviorCombo.h"
#include <list>
using namespace std;
//-------------------------------------------------------------------------
BehaviorCollection::BehaviorCollection() : m_uiCurPos(0)
{
	m_vBehaviors.push_back(NiNew Arrival());
	m_vBehaviors.push_back(NiNew Departure());
	m_vBehaviors.push_back(NiNew Seek());
	m_vBehaviors.push_back(NiNew Flee());
	m_vBehaviors.push_back(NiNew Wander());
	m_vBehaviors.push_back(NiNew Separation());
	m_vBehaviors.push_back(NiNew Alignment());
	m_vBehaviors.push_back(NiNew Cohesion());
	
	// flocking behavior
	list<BehaviorPtr> vFlocking;
	vFlocking.push_back(NiNew Cohesion());
	vFlocking.push_back(NiNew Alignment());
	vFlocking.push_back(NiNew Separation());
	vFlocking.push_back(NiNew Wander());

	list<float> vFlockingCoef;
	vFlockingCoef.push_back(1.0f);
	vFlockingCoef.push_back(4.0f);
	vFlockingCoef.push_back(5.0f);
	vFlockingCoef.push_back(5.0f);

	m_vBehaviors.push_back(NiNew BehaviorCombo("Flocking", vFlocking, vFlockingCoef));

	// arrive, wander and separate behavior
	list<BehaviorPtr> vAWS;
	vAWS.push_back(NiNew Arrival());
	vAWS.push_back(NiNew Wander());
	vAWS.push_back(NiNew Separation());

	list<float> vAWSCoef;
	vAWSCoef.push_back(1.0f);
	vAWSCoef.push_back(1.5f);
	vAWSCoef.push_back(5.0f);

	m_vBehaviors.push_back(NiNew BehaviorCombo("Arrive, Wander & Separate", vAWS, vAWSCoef));

}
//-------------------------------------------------------------------------
BehaviorCollection::~BehaviorCollection()
{
	for (unsigned int i=0; i<m_vBehaviors.size(); i++)
	{
		m_vBehaviors[i] = 0;
	}
	m_vBehaviors.clear();
}
//-------------------------------------------------------------------------
BehaviorPtr BehaviorCollection::GetNext() 
{
	size_t size = m_vBehaviors.size();
	if (size == 0) 
	{
		return 0;
	}
	m_uiCurPos = (m_uiCurPos + 1)%size;
	return m_vBehaviors[m_uiCurPos];

}
//-------------------------------------------------------------------------