#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "SingletonObj.h"
#include <NiInput.h>

class GameApp;

// Singleton Class
class InputManager : public SingletonObj<InputManager>
{
	friend SingletonObj<InputManager>;
public:
	// processes keyboard and mouse input
	void ProcessInput(NiInputSystemPtr inputSystem, GameApp* gameApp);
private:
	// private ctor / dtor
	InputManager();
	~InputManager();

	// handles keyboard
	void ProcessKeyboard(NiInputKeyboard* keyboard, GameApp* gameApp);
	// handles mouse
	void ProcessMouse(NiInputMouse* mouse, GameApp* gameApp);
};

#endif