/**
 * Handles user input. Singleton class.
 */
#include "InputManager.h"
#include "GameManager.h"
#include "GameApp.h"

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
		if (gameMgr->IsGameOver())
		{
			if (keyboard->KeyWasPressed(NiInputKeyboard::KEY_Y))
			{
				gameMgr->RestartGame();
				return;
			}
		}
		else
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
			
			// cycle through targets
			if(keyboard->KeyWasPressed(NiInputKeyboard::KEY_SPACE))
			{
				gameMgr->GetQueen()->SetTargetEnemy();			
			}

			// change selection mode
			if(keyboard->KeyWasPressed(NiInputKeyboard::KEY_LSHIFT))
			{
				gameMgr->SetSelectionMode(GameManager::SELECTION_GATHERERS);
			}

			if(keyboard->KeyWasReleased(NiInputKeyboard::KEY_LSHIFT))
			{
				gameMgr->SetSelectionMode(GameManager::SELECTION_SOLDIERS);
				gameMgr->GetQueen()->SetGather();
			}
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
		if (gameMgr->IsGameOver())
			return;

		// select more soldiers
		if(mouse->ButtonIsDown(NiInputMouse::NIM_LEFT))
		{
			gameMgr->SetStrongAttack(true);			
		}
		// stop selecting soldiers
		else if(mouse->ButtonWasReleased(NiInputMouse::NIM_LEFT))
		{
			gameMgr->SetStrongAttack(false);		
		}
	
		if(mouse->ButtonIsDown(NiInputMouse::NIM_RIGHT))
		{
			if (gameMgr->GetSelectionMode() == GameManager::SELECTION_GATHERERS)
			{
				gameMgr->GetQueen()->SetSelectGatherers();
			}
			else if (gameMgr->GetSelectionMode() == GameManager::SELECTION_SOLDIERS)
			{
				gameMgr->GetQueen()->SetSelectSoldiers();
			}
			
		}
	
		// stop rotating queen
		if(mouse->ButtonWasReleased(NiInputMouse::NIM_RIGHT))
		{		
			if (gameMgr->GetSelectionMode() == GameManager::SELECTION_GATHERERS)
			{
				gameMgr->GetQueen()->SetGather();
			}
			else if (gameMgr->GetSelectionMode() == GameManager::SELECTION_SOLDIERS)
			{
				gameMgr->GetQueen()->SetAttackEnemy();	
			}
		}
		
		gameMgr->GetQueen()->SetRotate((float)mx);
		gameMgr->GetQueen()->SetMoveVertical((float)my);
	}
	
}
//-------------------------------------------------------------------
