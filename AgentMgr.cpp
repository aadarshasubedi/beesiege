#include "AgentMgr.h"
#include "Agent.h"
#include "CharacterController.h"
#include "BehaviorCollection.h"
#include "Behavior.h"
using namespace std;

//-------------------------------------------------------------------------
AgentMgr::AgentMgr() : m_bSpringDynamicsOff (false),
					   m_spBehaviors( NiNew BehaviorCollection),
					   m_spCurrentBehavior(m_spBehaviors->GetCurrent())
{
}
//-------------------------------------------------------------------------
AgentMgr::~AgentMgr()
{
	list<AgentPtr>::iterator it;
	for (it = m_lAgents.begin(); it != m_lAgents.end(); it++)
	{
		if (*it) (*it) = 0;
	}

	m_lAgents.clear();
	
	m_spBehaviors = 0;
}
//-------------------------------------------------------------------------
void AgentMgr::AddAgent()
{
	/*
	NxVec3 pos = NxVec3(0.0f, 50.0f, 0.0f);
	NxVec3 dim = NxVec3(1.3f, 1.3f, 1.3f);
	NxActor* actor = PhysxMgr::Get()->CreateCapsule(pos, 1.0f, 2.0f, 1.0f);//CreateBox(pos, dim, 1.0f);//
	
	//NxQuat orientation; 
	//orientation.fromAngleAxis(90.0f, NxVec3(0.0, 0.0, 1.0));
	//actor->setGlobalOrientationQuat(orientation);

	NxMat33 rotY, rotZ, rotX;
	rotZ.rotZ(3.14f/2.0f);
	//rotZ.rotZ(3.14f/4.0f);
	//rotX.rotX(3.14f/2.0f);
	
	//actor->setGlobalOrientation(rotZ);
	
	AgentPtr agent = new Agent(actor);
	agent->GetController()->SetBehavior(m_pCurrentBehavior);
	agent->GetController()->ToggleSpringDynamics(m_bSpringDynamicsOff);
	m_lAgents.push_back(agent);
	*/
}
//-------------------------------------------------------------------------
void AgentMgr::UpdateAgents(const NxVec3& target)
{
	/*
	list<AgentPtr>::iterator it;
	for (it = m_lAgents.begin(); it != m_lAgents.end(); it++)
	{
		if (*it) 
		{
			(*it)->GetController()->Update(target);
		}
	}
	*/
}
//-------------------------------------------------------------------------
void AgentMgr::ToggleBehavior()
{
	/*
	m_spCurrentBehavior = m_spBehaviors->GetNext();
	list<AgentPtr>::iterator it;
	for (it = m_lAgents.begin(); it != m_lAgents.end(); it++)
	{
		if (*it) 
		{
			(*it)->GetController()->SetBehavior(m_spCurrentBehavior);		
		}
	}
	*/
}
//-------------------------------------------------------------------------
void AgentMgr::ToggleSpringDynamics()
{
	/*
	m_bSpringDynamicsOff = !m_bSpringDynamicsOff;
	list<AgentPtr>::iterator it;
	for (it = m_lAgents.begin(); it != m_lAgents.end(); it++)
	{
		if (*it) 
		{
			(*it)->GetController()->ToggleSpringDynamics(m_bSpringDynamicsOff);
		}
	}
	*/
}