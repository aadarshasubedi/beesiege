#include "State_Idle.h"

void StateIdle::Enter()
{

}
void StateIdle::Update(int t)
{

}

FSMState* StateIdle::CheckTransitions(int i)
{
	FSMState* dummyState = NiNew FSMState();
	return dummyState;
}

void StateIdle::Exit()
{

}

void StateIdle::Init()
{

}