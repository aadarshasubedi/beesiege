#include "FSM.h"
#include "FSMState.h"
#include "FSMAIControl.h"

FSMState::FSMState(FSMAIControl* control, int type) :
 m_type(type),
 m_control(control)
{ 
}

 FSMState::~FSMState()
 {
	 if (m_control)
	 {
		 m_control  = 0;
	 }
 }

void FSMState::Enter()
{

}
void FSMState::Exit()
{

}
void FSMState::Update(int t)
{

}
void FSMState::Init()
{

}
FSMState* FSMState::CheckTransitions(int t)
{
	//FSMState* dummyState;
	return 0;
}

