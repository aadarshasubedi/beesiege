#include "UIManager.h"

UIManager::UIManager()
{
	m_createHoneyBee.Initialize(this, &UIManager::createHoneyBee);
	m_createSoldierBee.Initialize(this, &UIManager::createHealerBee);
	m_createHealerBee.Initialize(this, &UIManager::createHealerBee);
	pkUIGroup2 = NiNew NiUIGroup("Bee factory", 0.0);
}

UIManager::~UIManager()
{
	/*m_spHoneyBeePolygon = 0;
	m_spSoldierBeePolygon = 0;
	m_spHealerBeePolygon = 0;*/
}

bool UIManager::CreateUI(GameApp* gameApp, float fCurrentHeight,float fOffset,
		float fElementWidth,float fElementHeight,float fUIGroupHeaderHeight)
{
	
    NiUIGroup* pkUIGroup = NiNew NiUIGroup("Create Bees", fUIGroupHeaderHeight);

    NiUIButton* pkButton = NiNew NiUIButton("Honey Bees");
    pkButton->SetOffset(fOffset, fCurrentHeight);
    pkButton->SetDimensions(0.15f, fElementHeight);
    pkButton->SubscribeToPressEvent(&m_createHoneyBee);
    pkButton->AddKeyboardHotkey(NiInputKeyboard::KEY_1);
    pkUIGroup->AddChild(pkButton);
    fCurrentHeight += fElementHeight;


    pkButton = NiNew NiUIButton("Soldier Bees");
    pkButton->SetOffset(fOffset, fCurrentHeight);
    pkButton->SetDimensions(0.15f, fElementHeight);
    pkButton->SubscribeToPressEvent(&m_createSoldierBee);
    pkButton->AddKeyboardHotkey(NiInputKeyboard::KEY_2);
    pkUIGroup->AddChild(pkButton);
    fCurrentHeight += fElementHeight;


    pkButton = NiNew NiUIButton("Healer Bees");
    pkButton->SetOffset(fOffset, fCurrentHeight);
    pkButton->SetDimensions(0.15f, fElementHeight);
    pkButton->SubscribeToPressEvent(&m_createHealerBee);
    pkButton->AddKeyboardHotkey(NiInputKeyboard::KEY_3);
    pkUIGroup->AddChild(pkButton);
    fCurrentHeight += fElementHeight;

    float fGroupWidth = fElementWidth + 2.0f * fOffset;
    pkUIGroup->SetOffset(1.0f - fGroupWidth, 0.0f);
    pkUIGroup->SetDimensions(fGroupWidth, fCurrentHeight + 
        0.5f * fElementHeight);
    pkUIGroup->UpdateRect();
    NiUIManager::GetUIManager()->AddUIGroup(pkUIGroup);

	pkUIGroup2->SetOffset(0.0,0.0f);
	pkUIGroup2->SetDimensions(fGroupWidth + 0.2, fCurrentHeight - 0.07);
    pkUIGroup2->UpdateRect();
	NiUIManager::GetUIManager()->AddUIGroup(pkUIGroup2);

    return true;
}

void UIManager::createSoldierBee()
{
	GameManager* gameMgr = GameManager::Get();
	gameMgr->GetGameApp()->beeCreationQueue.AddTail(ResourceManager::RES_MODEL_BEE);
	gameMgr->CreateObject3d(ResourceManager::RES_MODEL_BEE);

}

void UIManager::createHoneyBee()
{
	GameManager* gameMgr = GameManager::Get();
	gameMgr->GetGameApp()->beeCreationQueue.AddTail(ResourceManager::RES_MODEL_HONEYBEE);
	gameMgr->CreateObject3d(ResourceManager::RES_MODEL_HONEYBEE);
}

void UIManager::createHealerBee()
{
	GameManager* gameMgr = GameManager::Get();
	gameMgr->GetGameApp()->beeCreationQueue.AddTail(ResourceManager::RES_MODEL_HEALERBEE);
	gameMgr->CreateObject3d(ResourceManager::RES_MODEL_HEALERBEE);
}

