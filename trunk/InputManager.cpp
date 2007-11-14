/**
 * Handles user input. Singleton class.
 */
#include "InputManager.h"
#include "GameManager.h"
#include "GameApp.h"
#include "Bee.h"
#include "Locust.h"

//------------------------------------------------------------------- 
/** 
 * Ctor
 * 
 */
InputManager::InputManager()
{
}
//------------------------------------------------------------------- 
/** 
 * Dtor
 * 
 */
InputManager::~InputManager()
{
}
//------------------------------------------------------------------- 
/** 
 * Processes keyboard and mouse input
 * 
 * @param inputSystem
 * @param gameApp
 */
void InputManager::ProcessInput(NiInputSystemPtr inputSystem, GameApp* gameApp)
{
	ProcessKeyboard(inputSystem->GetKeyboard(), gameApp);
	ProcessMouse(inputSystem->GetMouse(), gameApp);
}
//------------------------------------------------------------------- 
/** 
 * Processes keyboard
 * 
 * @param keyboard
 * @param gameApp
 */
void InputManager::ProcessKeyboard(NiInputKeyboard* keyboard,GameApp* gameApp)
{
	GameManager* gameMgr = GameManager::Get();
	if (keyboard != 0)
    {
		// move queen forward
		if (keyboard->KeyIsDown(NiInputKeyboard::KEY_W))
		{
			gameMgr->GetQueen()->SetMoveForward();
		}
		// move queen backward
		else if (keyboard->KeyIsDown(NiInputKeyboard::KEY_S))
		{
			gameMgr->GetQueen()->SetMoveBackward();
		}
		// move queen left
		if (keyboard->KeyIsDown(NiInputKeyboard::KEY_A))
		{
			gameMgr->GetQueen()->SetMoveLeft();
		}
		// move queen right
		else if (keyboard->KeyIsDown(NiInputKeyboard::KEY_D))
		{
			gameMgr->GetQueen()->SetMoveRight();	
		}
		// add a bee
		if(keyboard->KeyWasPressed(NiInputKeyboard::KEY_SPACE))
		{
			BeePtr soldier = (Bee*)(GameObj3d*)gameMgr->CreateObject3d(ResourceManager::RES_MODEL_BEE);
			
			
		}
		
		// cycle through targets
		if(keyboard->KeyWasPressed(NiInputKeyboard::KEY_TAB))
		{
			gameMgr->GetQueen()->SetTargetEnemy();
			
		}
    }
}
//------------------------------------------------------------------- 
/** 
 * Processes mouse
 * 
 * @param mouse
 * @param gameApp
 */
void InputManager::ProcessMouse(NiInputMouse* mouse, GameApp* gameApp)
{
	if (mouse != NULL)
	{
		int mx, my, mz;
		mouse->GetPositionDelta(mx, my, mz);

		GameManager* gameMgr = GameManager::Get();

		// select more soldiers
		if(mouse->ButtonIsDown(NiInputMouse::NIM_LEFT))
		{
			gameMgr->GetQueen()->SetSelectSoldiers();
		}
		// stop selecting soldiers
		else if(mouse->ButtonWasReleased(NiInputMouse::NIM_LEFT))
		{
			gameMgr->GetQueen()->SetAttackEnemy();
		}
		// rotate view
		if(mouse->ButtonIsDown(NiInputMouse::NIM_RIGHT))
		{
			gameApp->GetCameraController()->RotateCamera((float)mx, (float)my);
		}
		// rotate queen
		else
		{
			gameMgr->GetQueen()->SetRotate((float)mx);
			gameMgr->GetQueen()->SetMoveVertical((float)my);
		}
		// stop rotating queen
		if(mouse->ButtonWasReleased(NiInputMouse::NIM_RIGHT))
		{
			gameApp->GetCameraController()->StopRotateCamera();
		}
		
	}
	
}
//-------------------------------------------------------------------
