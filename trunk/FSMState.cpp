/**
*	A FSM state
*/

#include "FSMState.h"
#include "FSMAIControl.h"

//------------------------------------------------------
/**
* Ctor
*/
FSMState::FSMState(FSMAIControl* control, int type) :
 m_type(type),
 m_control(control)
{ 
}
//------------------------------------------------------
/**
* Dtor
*/
FSMState::~FSMState()
{
 if (m_control)
 {
	 m_control  = 0;
 }
}

