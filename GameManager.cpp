/**
 * Holds game objects and updates them. Singleton class.
 */

#include <iostream>
#include <sstream>
#include <string>
#include "GameManager.h"
#include "GameObj3d.h"
#include "Bee.h"
#include "HealerBee.h"
#include "HoneyBee.h"
#include "Locust.h"
#include "Dragonfly.h"
#include "Boss.h"
#include "ConfigurationManager.h"
#include "TextManager.h"
#include "LevelManager.h"
#include <NiPhysXScene.h>
#include <NiApplication.h>
#include "EnemyBase.h"
#include "Flower.h"
using namespace std;
//------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
GameManager::GameManager() : 
m_fDeltaTime(0.0f), m_plAgents(0), m_pCurrentTarget(0),
m_fKillingRate(0.0f), m_fKillCount(0.0f), m_fLastKillTime(0.0f),
m_spAmbientSounds(0),m_pCurrentFlowerTarget(0), m_eSelectionMode(SELECTION_SOLDIERS),
m_bIsQueenAlive(true),m_bWin(false),m_icBasesCount(5),m_iCountBasesDestroyed(0)
{
}
//------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
GameManager::~GameManager()
{

	if (m_spAmbientSounds)
	{
		m_spAmbientSounds->Stop();
		m_spAmbientSounds = 0;
	}
	m_lObjects.RemoveAll();
	m_lEnemies.RemoveAll();
	m_lFlowers.RemoveAll();
	m_lBases.RemoveAll();
	m_spQueen = 0;
	m_spCurrentLevel = 0;
	ConfigurationManager::Destroy();
	LevelManager::Destroy();
}
//------------------------------------------------------------------------ 
/** 
 * Initializes manager
 * 
 * @param parent
 * @param physXScene
 * @param app
 * 
 * @return bool
 */
bool GameManager::Init(NiNodePtr parent, NiPhysXScenePtr physXScene, NiSample* app )
{
	// read configuration file
	m_pGameApplication = (GameApp*)app;
	if (!ConfigurationManager::Get()->ReadConfigurationFile(
		NiSample::ConvertMediaFilename("data/configuration.xml")))
	{
		NiMessageBox("Could Not Read Configuration File", "Error");
		return false;
	}

	m_fMaxPlayerHeight = ConfigurationManager::Get()->queen_maxHeight;
	m_fDefaultFogDepth = ConfigurationManager::Get()->scene_fogDefaultDepth;
	m_fFogScaleValue   = ConfigurationManager::Get()->queen_fogScaleValue;

	// create queen
	m_spQueen = NiNew Queen;
	if (!AddObject((GameObj3dPtr)m_spQueen, parent, physXScene))
	{
		return false;
	}
	m_spQueen->GetActor()->setGlobalPosition(NxVec3(0.0, 100.0, -200.0));

	if (!LevelManager::Get()->LoadLevel(1))
	{
		return false;
	}

	//m_spCurrentLevel = LevelManager::Get()->GetLevel(1);
	//CopyLists(m_spCurrentLevel->GetEnemies(), m_lEnemies);

	//if (!AddObject((GameObj3dPtr)(NiNew EnemyBase), parent))
	//{
	//	return false;
	//}
	
	
	// Create all the flowers in the scene
	CreateFlowers(parent);

	CreateEnemyBases(parent);

	m_spAmbientSounds = ResourceManager::Get()->GetSound(
		ResourceManager::RES_SOUND_AMBIENT, 0);
	if (m_spAmbientSounds)
	{
		m_spAmbientSounds->Play();
	}
	return true;
}
//------------------------------------------------------------------------
/**
*Creates all the flowers and tranlates them to its position in the scene
*/
void GameManager::CreateFlowers(NiNodePtr parent)
{	
	for(int i=1;i<37;i++)
	{
		stringstream s;
		s << i;
		string str1 = "attachmentBox" + s.str();
		
		NiFixedString s1 = str1.c_str();;
		NiNode* attacher1 = (NiNode*) parent->GetObjectByName(s1);
		FlowerPtr flower = (Flower*)(GameObj3d*)CreateObject3d(ResourceManager::RES_MODEL_FLOWER);
		flower->GetNode()->SetTranslate(attacher1->GetTranslate());
		
	}
}

//------------------------------------------------------------------------
/**
*Creates all the flowers and tranlates them to its position in the scene
*/
void GameManager::CreateEnemyBases(NiNodePtr parent)
{	
	for(int i=1;i<m_icBasesCount+1;i++)
	{
		stringstream s;
		s << i;
		string str1 = "enemyBase" + s.str();
	
		NiFixedString s1 = str1.c_str();
		NiNode* attacher2 = (NiNode*) parent->GetObjectByName(s1);
		EnemyBasePtr enemyBase = (EnemyBase*)(GameObj3d*)CreateObject3d(ResourceManager::RES_MODEL_BASE);
		if(enemyBase)
		{
			enemyBase->GetNode()->SetTranslate(attacher2->GetTranslate());
		}
		
	}
}

//------------------------------------------------------------------------ 
/** 
 * Updates all game objects
 * 
 * @param fTime
 */
void GameManager::UpdateAll(float fTime)
{
	if (!m_bIsQueenAlive)
	{
		TextManager::Get()->UpdateText(TextManager::STRING_GAMEOVER,"Game Over!!!\nRestart?\n(Press Y for yes or Esc for no)");
		return;
	}
	else if (m_bWin)
	{
		TextManager::Get()->UpdateText(TextManager::STRING_WIN,"You Win!!!\nRestart?\n(Press Y for yes or Esc for no)");
		return;
	}

	m_fDeltaTime = m_pGameApplication->GetFrameTime();
	NiTListIterator it = m_lObjects.GetHeadPos();
	int size = m_lObjects.GetSize();
	for (int i=0; i<size; i++)
	{
		GameObj3dPtr obj = m_lObjects.Get(it);
		if (!obj) break;
		if (!obj->IsActive())
		{
			if (NiIsKindOf(Enemy, obj))
			{
				RemoveEnemy((Enemy*)(GameObj3d*)obj);				
			}
			else if (NiIsKindOf(Bee, obj))
			{
				GetQueen()->RemoveSoldier((Bee*)(GameObj3d*)obj);
			}
			else if (NiIsKindOf(HealerBee, obj))
			{
				GetQueen()->RemoveHealer((HealerBee*)(GameObj3d*)obj);
			}
			else if (NiIsKindOf(HoneyBee, obj))
			{
				GetQueen()->RemoveGatherer((HoneyBee*)(GameObj3d*)obj);
			}
			RemoveObject(obj);
			m_lObjects.RemovePos(it);			
			continue;
		}
		obj->Update(fTime);
		it = m_lObjects.GetNextPos(it);
	}

	// update fog
	NiFogProperty* fog = (NiFogProperty*)m_pGameApplication->GetScene()->GetProperty(NiProperty::FOG);
	if (fog)
	{
		fog->SetDepth(m_fDefaultFogDepth);
	}
}
//------------------------------------------------------------------------ 
/**
* Creates a 3d object of a given type and returns 
* that object to the caller
* @param ResourceManager::ResourceType: the type
*/
GameObj3dPtr GameManager::CreateObject3d(ResourceManager::ResourceType type)
{
	NiNodePtr mainScene = m_pGameApplication->GetScene();
	NiPhysXScenePtr physxScene = m_pGameApplication->GetPhysXScene();
	GameObj3dPtr obj = 0;
	switch (type)
	{
	case ResourceManager::RES_MODEL_BEE:
			obj = NiNew Bee;
			if (!AddObject(obj, mainScene, physxScene))
			{
				obj = 0;
			}
			break;
	case ResourceManager::RES_MODEL_HEALERBEE:
			obj = NiNew HealerBee;
			if (!AddObject(obj, mainScene, physxScene))
			{
				obj = 0;
			}
			break;
	case ResourceManager::RES_MODEL_HONEYBEE:
			obj = NiNew HoneyBee;
			if (!AddObject(obj, mainScene, physxScene))
			{
				obj = 0;
			}
			break;
	case ResourceManager::RES_MODEL_QUEEN:
			obj = NiNew Queen;
			if (!AddObject(obj, mainScene, physxScene))
			{
				obj = 0;
			}
			break;
	case ResourceManager::RES_MODEL_LOCUST:
			obj = NiNew Locust;
			if (!AddObject(obj, mainScene, physxScene))
			{
				obj = 0;
			}
			m_lEnemies.AddTail((Enemy*)(GameObj3d*)obj);
			break;
	case ResourceManager::RES_MODEL_DRAGONFLY:
			obj = NiNew DragonFly;
			if (!AddObject(obj, mainScene, physxScene))
			{
				obj = 0;
			}
			m_lEnemies.AddTail((Enemy*)(GameObj3d*)obj);
			break;
	case ResourceManager::RES_MODEL_BOSS:
			obj = NiNew Boss;
			if (!AddObject(obj, mainScene, physxScene))
			{
				obj = 0;
			}
			m_lEnemies.AddTail((Enemy*)(GameObj3d*)obj);
			break;
	case ResourceManager::RES_MODEL_FLOWER:
		obj = NiNew Flower;
			if (!AddObject(obj, mainScene))
			{
				obj = 0;
			}
			m_lFlowers.AddTail((Flower*)(GameObj3d*)obj);
			break;
	case ResourceManager::RES_MODEL_BASE:
		obj = NiNew EnemyBase;
			if (!AddObject(obj, mainScene))
			{
				obj = 0;
			}
			m_lBases.AddTail((EnemyBase*)(GameObj3d*)obj);
			break;
	default:
		return 0;
	}

	return obj;
}
//------------------------------------------------------------------------ 
/**
* Increases kill count, and calculates killing rate
*/
void GameManager::RecordKill()
{
	float killingInterval = m_pGameApplication->GetAccumTime() -
		m_fLastKillTime;

	m_fLastKillTime = m_pGameApplication->GetAccumTime();

	m_fKillCount += 1.0f;
	m_fKillingRate += (killingInterval - m_fKillingRate)/ m_fKillCount;
}
//------------------------------------------------------------------------ 
/** 
 * Adds an object to the list
 * 
 * @param object
 * @param parent
 * 
 * @return bool
 */
bool GameManager::AddObject(GameObj3dPtr object, NiNodePtr parent)
{
	if (object->Init(parent))
	{
		m_lObjects.AddTail(object);
		
		return true;
	}
	
	return false;
}
//------------------------------------------------------------------------ 
/** 
 * Adds a PhysX object to the list
 * 
 * @param object
 * @param parent
 * @param physXScene
 * 
 * @return bool
 */
bool GameManager::AddObject(GameObj3dPtr object, NiNodePtr parent, NiPhysXScenePtr physXScene)
{
	if (object->Init(parent, physXScene))
	{
		m_lObjects.AddTail(object);
		
		return true;
	}
	
	return false;
}
//------------------------------------------------------------------------ 
/** 
 * Removes an object from the list
 * 
 * @param object
 */
void GameManager::RemoveObject(GameObj3dPtr object)
{
	if (!object) return;
	// remove physx prop and actor from scene
	NiPhysXPropPtr prop = object->GetTheProp();
	if (prop)
	{
		prop->DetachSceneCallback(m_pGameApplication->GetPhysXScene());
		if (NiIsKindOf(GameCharacter, object))
		{
			((GameCharacter*)(GameObj3d*)object)->ResetActor(0);
		}
	}

	// remove scene node
	NiNode* parent = object->GetNode()->GetParent();
	if (parent)
		parent->DetachChild(object->GetNode());

	
	
}
//------------------------------------------------------------------------
/** 
 * Removes an enemy from the list
 * 
 * @param agent
 */
void GameManager::RemoveEnemy(EnemyPtr enemy)
{
	if (!m_lEnemies.IsEmpty())
	{
		m_lEnemies.Remove(enemy);
	}
}
//------------------------------------------------------------------------
/** 
 * Restarts game
 * 
 */
void GameManager::RestartGame()
{
	if (m_spAmbientSounds)
	{
		m_spAmbientSounds->Stop();
	}

	m_pCurrentTarget = 0;
	m_pCurrentFlowerTarget = 0;
	NiTListIterator it = m_lObjects.GetHeadPos();
	int size = m_lObjects.GetSize();
	for (int i=0; i<size; i++)
	{
		if (NiIsKindOf(Queen, m_lObjects.Get(it)) ||
			NiIsKindOf(Flower, m_lObjects.Get(it)) ||
			NiIsKindOf(EnemyBase, m_lObjects.Get(it)))
		{
			it = m_lObjects.GetNextPos(it);
			continue;
		}
		else
		{
			RemoveObject(m_lObjects.Get(it));
			m_lObjects.RemovePos(it);
		}
	}

	m_spQueen->Reset();
	m_spQueen->GetActor()->setGlobalPosition(NxVec3(0.0, 100.0, -200.0));

	m_lEnemies.RemoveAll();
	m_plAgents = 0;
	
	it = m_lFlowers.GetHeadPos();
	size = m_lFlowers.GetSize();
	for (int i=0; i<size; i++)
	{
		m_lFlowers.Get(it)->ResetHoney();
	}

	
	it = m_lBases.GetHeadPos();
	size = m_lBases.GetSize();
	for (int i=0; i<size; i++)
	{
		m_lBases.Get(it)->Reset();
	}
	

	if (m_spAmbientSounds)
	{
		m_spAmbientSounds->Play();
	}

	m_bIsQueenAlive = true;
	m_bWin = false;

	m_fKillingRate = 0.0f;
	
	m_fKillCount = 0.0f;

	m_fLastKillTime = 0.0f;

	TextManager::Get()->UpdateText(TextManager::STRING_GAMEOVER,"");
	TextManager::Get()->UpdateText(TextManager::STRING_WIN,"");
}
