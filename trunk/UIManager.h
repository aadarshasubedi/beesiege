#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "SingletonObj.h"
#include "GameApp.h"
#include "GameManager.h"

class GameApp;

class UIManager: public SingletonObj<UIManager>
{
public:
	UIManager();
	~UIManager();
	//creates UI elements
	bool CreateUI(GameApp* gameApp,float fCurrentHeight,float fOffset,
		float fElementWidth,float fElementHeight,float fUIGroupHeaderHeight);

private:
	// creates screen polygons
	void createSoldierBee();
	void createHoneyBee();
	void createHealerBee();
	NiUIGroup* pkUIGroup2;
	
	NiUIMemberSlot0<UIManager> m_createHoneyBee;
    NiUIMemberSlot0<UIManager> m_createHealerBee;
	NiUIMemberSlot0<UIManager> m_createSoldierBee;
	//NiScreenElementsPtr m_spHoneyBeePolygon;
	//NiScreenElementsPtr m_spSoldierBeePolygon;
	//NiScreenElementsPtr m_spHealerBeePolygon;
	
};

#endif