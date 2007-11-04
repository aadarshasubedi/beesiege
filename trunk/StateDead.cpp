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
	
	FSMState* dummyState = NiNew FSMState();
	return dummyState;
}

void StateDead::Exit()
{
	FSMAIControl* control = m_control;
	GameCharacter* character = m_control->m_character;

	delete character;
}

void StateDead::Init()
{

}