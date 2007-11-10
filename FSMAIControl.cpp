#include "FSMAIControl.h"
#include "FSMMachine.h"

FSMAIControl::FSMAIControl(GameCharacter* character) : m_character(character),
													   m_machine(NiNew FSMMachine()),
													   m_fcPowerUpScanDistance(30.0f)
{
}

FSMAIControl::~FSMAIControl()
{
	NiDelete m_machine;
	m_machine = 0;
}
	
void FSMAIControl::Update(int t)
{
	UpdatePerceptions(t);
	m_machine->UpdateMachine(t);	

	DoExtraUpdates(t);
}
void FSMAIControl::UpdatePerceptions(int t)
{

}
void FSMAIControl::Init()
{

}

