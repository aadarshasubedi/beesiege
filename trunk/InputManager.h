#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "SingletonObj.h"
#include <NiInput.h>

class GameApp;

class InputManager : public SingletonObj<InputManager>
{
	friend SingletonObj<InputManager>;
public:
	void ProcessInput(NiInputSystemPtr inputSystem, GameApp* gameApp);
private:
	InputManager();
	~InputManager();

	void ProcessKeyboard(NiInputKeyboard* keyboard, GameApp* gameApp);
	void ProcessMouse(NiInputMouse* mouse, GameApp* gameApp);
};

#endif