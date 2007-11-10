#include "State_Queen_Dead.h"
#include "FSMMachine.h"

void StateQueenDead::Enter()
{

}
void StateQueenDead::Update(int t)
{
	//free the memory for this GameCharacter
	Exit();
	
}

FSMState* StateQueenDead::CheckTransitions(int i)
{
	//always return the dead state
	FSMState* nextState = ((FSMQueenAIControl*)m_control)->m_machine->m_currentState;
	return nextState;
}

void StateQueenDead::Exit()
{
	FSMAIControl* control = m_control;
	//delete ((FSMQueenAIControl*)m_control)->m_queen;
}

void StateQueenDead::Init()
{

}