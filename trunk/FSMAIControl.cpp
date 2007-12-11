/**
* An AI controller that uses a Finite State Machine
* and an Agent to control a character
*/

#include "FSMAIControl.h"
#include "GameManager.h"

//------------------------------------------------------------
NiImplementRTTI(FSMAIControl,ControllerAttr);
//------------------------------------------------------------
/**
* Ctor
* @param The character that needs to be controlled
*/
FSMAIControl::FSMAIControl(GameCharacter* character)
: ControllerAttr(character),
  m_spMachine(NiNew FSMMachine()),
  m_spAgent(NiNew Agent(character->GetActor())),
  m_pGameManager(GameManager::Get())
{
}
//------------------------------------------------------------
/**
* Dtor
* 
*/
FSMAIControl::~FSMAIControl()
{
	m_spMachine = 0;
	m_spAgent = 0;
}
//------------------------------------------------------------
/**
* Updates the controller's FSM
* @param delta time
*/	
void FSMAIControl::Update(float fTime)
{
	UpdatePerceptions(fTime);
	m_spMachine->UpdateMachine(fTime);
	DoExtraUpdates(fTime);
}

