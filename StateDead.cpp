#include "State_Dead.h"

void StateDead::Enter()
{

}
void StateDead::Update(int t)
{

}

FSMState* StateDead::CheckTransitions(int i)
{
	FSMState* dummyState = NiNew FSMState();
	return dummyState;
}

void StateDead::Exit()
{

}

void StateDead::Init()
{

}