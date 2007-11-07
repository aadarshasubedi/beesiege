#include "State_Dead.h"

void StateDead::Enter()
{

}
void StateDead::Update(int t)
{
	//free the memory for this GameCharacter
	Exit();
	
}

FSMState* StateDead::CheckTransitions(int i)
{
	//always return the dead state
	FSMState* nextState; //= (m_control)->m_machine->m_currentState;
	
	return nextState;
}

void StateDead::Exit()
{
	FSMAIControl* control = m_control;
	delete m_control->m_character;
}

void StateDead::Init()
{

}