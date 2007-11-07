#include "State_Bee_Dead.h"

void StateBeeDead::Enter()
{

}
void StateBeeDead::Update(int t)
{
	//free the memory for this GameCharacter
	Exit();
	
}

FSMState* StateBeeDead::CheckTransitions(int i)
{
	//always return the dead state
	FSMState* nextState = ((FSMBeeAIControl*)m_control)->m_bee_machine->m_currentState;
	return nextState;
}

void StateBeeDead::Exit()
{
	FSMAIControl* control = m_control;
	//delete ((FSMBeeAIControl*)m_control)->m_bee;
}

void StateBeeDead::Init()
{

}