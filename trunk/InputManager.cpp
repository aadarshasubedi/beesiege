#include "InputManager.h"
#include "GameManager.h"
#include "GameApp.h"
#include "Bee.h"
//-------------------------------------------------------------------
InputManager::InputManager()
{
}
//-------------------------------------------------------------------
InputManager::~InputManager()
{
}
//-------------------------------------------------------------------
void InputManager::ProcessInput(NiInputSystemPtr inputSystem, GameApp* gameApp)
{
	ProcessKeyboard(inputSystem->GetKeyboard(), gameApp);
	ProcessMouse(inputSystem->GetMouse(), gameApp);
}
//-------------------------------------------------------------------
void InputManager::ProcessKeyboard(NiInputKeyboard* keyboard,GameApp* gameApp)
{
	GameManager* gameMgr = GameManager::Get();
	if (keyboard != 0)
    {
		if (keyboard->KeyIsDown(NiInputKeyboard::KEY_W))
		{
			gameMgr->GetQueen()->MoveForward();
		}
		else if (keyboard->KeyIsDown(NiInputKeyboard::KEY_S))
		{
			gameMgr->GetQueen()->MoveBack();
		}

		if (keyboard->KeyIsDown(NiInputKeyboard::KEY_A))
		{
			gameMgr->GetQueen()->StrafeLeft();
		}
		else if (keyboard->KeyIsDown(NiInputKeyboard::KEY_D))
		{
			gameMgr->GetQueen()->StrafeRight();	
		}

		if(keyboard->KeyWasPressed(NiInputKeyboard::KEY_SPACE))
		{
			gameMgr->AddObject((GameObj3dPtr)(NiNew Bee), gameApp->GetScene(), gameApp->GetPhysXScene());
		}
    }
}
//-------------------------------------------------------------------
void InputManager::ProcessMouse(NiInputMouse* mouse, GameApp* gameApp)
{
	if (mouse != NULL)
	{
		int mx, my, mz;
		mouse->GetPositionDelta(mx, my, mz);

		GameManager::Get()->GetQueen()->Rotate((float)mx, (float)my);
	}
	
}
//-------------------------------------------------------------------
