/**
 * The project's 'main' class. It inherits from NiApplication 
 * and is responsible for running the game 
 */

#include "GameApp.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "ConfigurationManager.h"
#include "CameraController.h"
#include "InputManager.h"
#include "TextManager.h"
#include "SoundManager.h"
#include "UIManager.h"
#include <NiFogProperty.h>
#include <NiSystemCursor.h>
#include <math.h>
#include "HealthAttribute.h"


#pragma comment(lib, "NiBinaryShaderLibDX9.lib")
#pragma comment(lib, "NiD3D10BinaryShaderLibD3D10.lib")
#pragma comment(lib, "NSBShaderLibDX9.lib")
#pragma comment(lib, "NSFParserLibDX9.lib")

//--------------------------------------------------------------------------- 
/** Creates a new NiApplication* 
 * 
 * @return NiSample*
 */
NiApplication* NiApplication::Create()
{
    return NiNew GameApp;
	
}
//--------------------------------------------------------------------------- 
/** 
 * The constructor
 * 
 */
//GameApp::GameApp() : NiApplication("BeeSiege",
//    DEFAULT_WIDTH, DEFAULT_HEIGHT), m_fLastSimTime(0.0f)
GameApp::GameApp():NiSample("BeeSiege",DEFAULT_WIDTH, DEFAULT_HEIGHT),m_fLastSimTime(0.0f),hasQueueChanged(false),hasAlphaChanged(false),alphaValue(1.0),
initialQueueOffset(950.0)
{
	NiSample::SetMediaPath("../../res/");
	m_bUseNavSystem = false;
	//SetMediaPath("../../res/");
	
}
//---------------------------------------------------------------------- 
/** 
 * Initializes NiSample
 * 
 * 
 * @return bool
 */
bool GameApp::Initialize()
{
	srand((unsigned int)time(0));
	// initialize PhysX
	m_pPhysXManager = NiPhysXManager::GetPhysXManager();
	if (!m_pPhysXManager->Initialize())
        return false;
    SetPhysXSDKParams();

	if (!NiSample::Initialize())
		return false;
	ShowPointer();
	return true;
}
//---------------------------------------------------------------------- 
/** 
 * Creates the NiSample's scene
 * 
 * 
 * @return bool
 */
bool GameApp::CreateScene()
{

	// Because our scene will have some billboards with alpha, we use 
    // a NiAlphaAccumulator in order that our alpha gets sorted and drawn
    // correctly.5
    NiAlphaAccumulator* pkAccum = NiNew NiAlphaAccumulator;
    m_spRenderer->SetSorter(pkAccum);
	NiColor backgroundColor(0.0, 0.46, 0.99);
	m_spRenderer->SetBackgroundColor(backgroundColor);

    NiStream kStream;

	SetMaxFrameRate(120.0f);

	// create the main PhysX scene
	if (!CreatePhysXScene())
	{
		return false;
	}

	// load resources
	bool bSuccess = ResourceManager::Get()->Init(&kStream, m_spRenderer);
	if (!bSuccess) return false;

	// load main scene (better to be done separately than doing it in 
	// the ResourceManager, because it might have multiple PhysX props
    bSuccess = kStream.Load(
        //NiApplication::ConvertMediaFilename("models/final_again_1.nif"));
	    NiSample::ConvertMediaFilename("models/temp_final4.nif"));
    
    if (!bSuccess)
    {
        NiMessageBox("main scene file could not be loaded!", "NIF Error");
        return false;
    }

	m_spScene = 0;
	for (unsigned int i=0; i<kStream.GetObjectCount(); i++)
	{
		NiObject* pkObject = kStream.GetObjectAt(i);
		if (NiIsKindOf(NiNode, pkObject) && !m_spScene)
		{
			m_spScene = (NiNode*)pkObject;
		}
		else if (NiIsKindOf(NiPhysXProp, pkObject))
		{			
			m_spPhysXScene->AddProp((NiPhysXProp*)pkObject);
		}
	}
	
    NIASSERT(NiIsKindOf(NiNode, m_spScene));

	NiFogPropertyPtr fog = NiNew NiFogProperty;
	fog->SetFog(true);
	fog->SetDepth(ConfigurationManager::Get()->scene_fogDefaultDepth);
	fog->SetFogFunction(NiFogProperty::FOG_RANGE_SQ);
	fog->SetFogColor(backgroundColor);
	m_spScene->AttachProperty(fog);

	
	// init game manager
	bSuccess = GameManager::Get()->Init(m_spScene, m_spPhysXScene, this);
	if (!bSuccess) return false;

	// init text manager
	bSuccess = TextManager::Get()->Init(m_spRenderer);
	if (!bSuccess) return false;

	// We expect the queen to have been exported with a camera, so
	// we look for it here.
	m_spCamera = FindFirstCamera(GameManager::Get()->GetQueen()->GetNode());
    if (!m_spCamera)
    {
        NiMessageBox("The NIF file has no camera!", "Camera Error");
        return false;
    }

	// create a new CameraController for our camera
	m_spCameraController = NiNew CameraController(m_spCamera);

	// Update the scene graph before rendering begins.
    m_spScene->UpdateProperties();
    m_spScene->UpdateEffects();
    m_spScene->Update(0.0f);
    
    // Get simulation started. We give a small timestep to avoid zero length
    // steps, which cause problems with PhysX hardware in v2.3.2
    m_spPhysXScene->UpdateSources(0.001f);
    m_spPhysXScene->Simulate(0.001f);
    m_fLastSimTime = 0.001f;

	//draw the rectangles for the bees onto the screen
	CreateScreenPolygon("Textures/honey_bee_smaller.bmp", 20.0f, 60.0f, 1.0f);
	CreateScreenPolygon("Textures/soldier_bee_smaller.bmp", 20.0f, 110.0f, 1.0f);
	CreateScreenPolygon("Textures/healer_bee_smaller.bmp", 20.0f,160.0f, 1.0f);
	/*GetScreenTextures().AddTail(m_spHoneyBeePolygon);
	GetScreenTextures().AddTail(m_spSoldierBeePolygon);
	GetScreenTextures().AddTail(m_spHealerBeePolygon);*/

    return bSuccess;
}

bool GameApp::CreateUIElements()
{
    unsigned int uiX, uiY;
    m_spRenderer->GetOnScreenCoord(0.0f, 0.0f, 0, 0, uiX, uiY, 
        NiRenderer::CORNER_TOP_LEFT);

    float fCurHeight = m_kUIElementGroupOffset.y;
    float fOffset = m_kUIElementGroupOffset.x;
   
	UIManager::Get()->CreateUI(this,fCurHeight,fOffset,m_fUIElementWidth,m_fUIElementHeight,m_fUIGroupHeaderHeight);

    return true;
}
//---------------------------------------------------------------------- 
/** 
 * Processes user input
 * 
 */
void GameApp::ProcessInput()
{
	NiSample::ProcessInput();

	if (GetInputSystem())
	{
		InputManager::Get()->ProcessInput(GetInputSystem(), this);
	}
	
}
//--------------------------------------------------------------------- 
/** 
 * Updates the current frame
 * 
 */
void GameApp::UpdateFrame()
{
	// fetch previous frame's simulation results
	m_spPhysXScene->FetchResults(m_fLastSimTime, true);
    m_spPhysXScene->UpdateDestinations(m_fLastSimTime);

	 // Calls process input
    NiSample::UpdateFrame();

	// Update all of our GameObj3ds
	GameManager::Get()->UpdateAll(m_fAccumTime);
	
	m_spScene->Update(m_fAccumTime);
	m_spScene->UpdateProperties();
	m_spScene->UpdateEffects();

	// Update the current listener position (for sound - FMOD)
	NxActor* queenActor = 0;
	if (GameManager::Get()->GetQueen())
	{
		queenActor = GameManager::Get()->GetQueen()->GetActor();
		NxVec3 nxPos = queenActor->getGlobalPosition()/50.0f;
		NxVec3 nxVel = queenActor->getLinearVelocity() / 50.0f;
		NxVec3 nxFor = queenActor->getGlobalOrientation().getColumn(0);
		
		
		SoundManager::Get()->Update(nxPos,
									nxVel,
									NxVec3(0.0, 1.0, 0.0),nxFor);
	}
	else
	{
		SoundManager::Get()->Update();
	}

    // Now we start the next step, giving a time that will actually be
    // in the past by the time we get the results.
    m_spPhysXScene->UpdateSources(m_fAccumTime);
	m_spCameraController->Update(m_fAccumTime);
	m_spPhysXScene->Simulate(m_fAccumTime);
    m_fLastSimTime = m_fAccumTime;
	
	//check whether the bee is to be created now and if it is then remove it from the queue
	CreateBees();
	UpdateBeeQueue();

	char* qValue = new char[5];
	HealthAttribute* health = (HealthAttribute*)(GameManager::Get()->GetQueen())->GetAttribute(GameCharacter::ATTR_HEALTH);
	sprintf(qValue,"%.1f", health->GetHealth());

	TextManager::Get()->UpdateText(TextManager::STRING_QUEENHEALTH, qValue);

	sprintf(qValue, "%.1f", GameManager::Get()->GetQueen()->GetHoney());
	TextManager::Get()->UpdateText(TextManager::STRING_QUEENHONEY, qValue);

}
//--------------------------------------------------------------------------- 
/** 
 * Renders HUD
 * 
 */
void GameApp::RenderScreenItems()
{
	NiSample::RenderScreenItems();
	TextManager::Get()->DisplayText();
}
//--------------------------------------------------------------------
/**
* Updates the bee queue display
*/
void GameApp::UpdateBeeQueue()
{
	int queueSize = beeTypesQueue.GetSize();
	NiTListIterator index = beeTypesQueue.GetHeadPos();
	//NiTListIterator timeIndex = beeTimeQueue.GetHeadPos();

	float drawOffset = initialQueueOffset;
	int beeType;

	if(hasAlphaChanged)
	{
		if(beeTypesQueue.GetSize() > 0)
		{
			if(beeTypesQueue.GetHead() == ResourceManager::RES_MODEL_BEE)
					ChangeAlphaOfHeadTexture("Textures/soldier_bee_smaller.bmp", drawOffset, 60.0f, alphaValue);
			else if(beeTypesQueue.GetHead() == ResourceManager::RES_MODEL_HONEYBEE)
					ChangeAlphaOfHeadTexture("Textures/honey_bee_smaller.bmp", drawOffset, 60.0f, alphaValue);
			else if(beeTypesQueue.GetHead() == ResourceManager::RES_MODEL_HEALERBEE)
					ChangeAlphaOfHeadTexture("Textures/healer_bee_smaller.bmp", drawOffset, 60.0f, alphaValue);
		}
		hasAlphaChanged = false;
	}
	
	if(hasQueueChanged)
	{
		GetScreenTextures().RemoveAll();
		CreateScreenPolygon("Textures/honey_bee_smaller.bmp", 20.0f, 60.0f, 1.0f);
		CreateScreenPolygon("Textures/soldier_bee_smaller.bmp", 20.0f, 110.0f, 1.0f);
		CreateScreenPolygon("Textures/healer_bee_smaller.bmp", 20.0f,160.0f, 1.0f);
		
		if(beeTypesQueue.GetSize() > 0)
		{
			if(beeTypesQueue.GetHead() == ResourceManager::RES_MODEL_BEE)
				CreateScreenPolygon("Textures/soldier_bee_smaller.bmp", drawOffset, 60.0f, alphaValue);
			else if(beeTypesQueue.GetHead() == ResourceManager::RES_MODEL_HONEYBEE)
					CreateScreenPolygon("Textures/honey_bee_smaller.bmp", drawOffset, 60.0f, alphaValue);
			else if(beeTypesQueue.GetHead() == ResourceManager::RES_MODEL_HEALERBEE)
					CreateScreenPolygon("Textures/healer_bee_smaller.bmp", drawOffset, 60.0f, alphaValue);
			drawOffset -= 50.0f;
			if(beeTypesQueue.GetSize() > 1)
			{
				index = beeTypesQueue.GetNextPos(index);
				for(int i = 1;i<queueSize; i++)
				{
					beeType = beeTypesQueue.Get(index);
					if(beeType == ResourceManager::RES_MODEL_BEE)
						CreateScreenPolygon("Textures/soldier_bee_smaller.bmp", drawOffset, 60.0f, 1.0f);
					else if(beeType == ResourceManager::RES_MODEL_HONEYBEE)
						CreateScreenPolygon("Textures/honey_bee_smaller.bmp", drawOffset, 60.0f, 1.0f);
					else if(beeType == ResourceManager::RES_MODEL_HEALERBEE)
						CreateScreenPolygon("Textures/healer_bee_smaller.bmp", drawOffset, 60.0f, 1.0f);

					drawOffset -= 50.0;
					index = beeTypesQueue.GetNextPos(index);
				}
			}
		}
		hasQueueChanged = false;
		hasAlphaChanged = false;
	}

}

//---------------------------------------------------------------------
/**
* Creates bees that are in queue and have completed their wait time
*/
void GameApp::CreateBees()
{
	int queueSize = beeTimeQueue.GetSize();
	NiTListIterator indexTime = beeTimeQueue.GetHeadPos();
	NiTListIterator indexType = beeTypesQueue.GetHeadPos();
	float beeTimeComplete;
	int beeType;
	
	for(int i = 0;i<queueSize; i++)
	{
		beeTimeComplete = beeTimeQueue.Get(indexTime);
		if(m_fAccumTime >= beeTimeComplete)
		{
			beeType = beeTypesQueue.Get(indexType);
			GameManager::Get()->CreateObject3d(ResourceManager::ResourceType(beeType));
			beeTypesQueue.RemovePos(indexType);
			beeTimeQueue.RemovePos(indexTime);
			i++;
			hasQueueChanged = true;
			hasAlphaChanged = false;
		}
		else
		{
			indexTime = beeTimeQueue.GetNextPos(indexTime);
			indexType = beeTypesQueue.GetNextPos(indexType);
		}
			
	}

	if(beeTimeQueue.GetSize() > 0)
	{
		float timeDiff = beeTimeQueue.GetHead() - m_fAccumTime;
		if(timeDiff <= 5.0f && timeDiff > 0.0f)
		{
			/*for(float i = 5; i>=1; i--)
			{
				if((i/timeDiff) == 1.0f)
				{*/
					hasAlphaChanged = true;
					alphaValue = timeDiff*0.1;
					//break;
				//}
					
			//}
		}
		else
			alphaValue = 1.0;
	}
}
//--------------------------------------------------------------------- 
/** 
 * Frees memory
 * 
 */
void GameApp::Terminate()
{
	m_spCameraController = 0;
	m_spPhysXScene = 0;
	TextManager::Destroy();
	GameManager::Destroy();
	ResourceManager::Destroy();
	InputManager::Destroy();
	NiSample::Terminate();
	if (m_pPhysXManager)
        m_pPhysXManager->Shutdown();

}
//------------------------------------------------------------------------ 
/** 
 * Sets the default PhysX parameters
 * 
 * @param kParam
 */
void GameApp::SetPhysXSDKParams(const NxParameter kParam)
{
    if (!m_pPhysXManager)
        return;

    m_pPhysXManager->WaitSDKLock();

	NiPhysXSDKDescPtr pSDKDefaults = NiNew NiPhysXSDKDesc;
	pSDKDefaults->FromSDK();
    pSDKDefaults->SetParameter(NX_VISUALIZE_BODY_AXES, 1.0f);
    pSDKDefaults->SetParameter(NX_VISUALIZE_COLLISION_SHAPES, 1.0f);
  
    if (kParam == NX_PARAMS_NUM_VALUES)
    {
        pSDKDefaults->ToSDK();
    }
    else
    {
        m_pPhysXManager->m_pkPhysXSDK->setParameter(kParam,
            pSDKDefaults->GetParameter(kParam));
    }
     
	pSDKDefaults = 0;
    m_pPhysXManager->ReleaseSDKLock();
	
}
//------------------------------------------------------------------------ 
/** 
 * 
 * Creates the main PhysX scene
 * 
 * @return bool
 */
bool GameApp::CreatePhysXScene()
{
    // check for hardware
    bool bHaveHardware = m_pPhysXManager->m_pkPhysXSDK->getHWVersion() > 0;
      
    NxSceneDesc kNxSceneDesc;
    kNxSceneDesc.simType = NX_SIMULATION_SW;
	NiPoint3 gravity(0.0, 0.0, 0.0);
    NiPhysXTypes::NiPoint3ToNxVec3(gravity, kNxSceneDesc.gravity);

    if (bHaveHardware)
    {
		kNxSceneDesc.simType = NX_SIMULATION_HW;
    }
      
    m_spPhysXScene = NiNew NiPhysXScene();
    
    m_pPhysXManager->WaitSDKLock();
    NxScene* pkNxScene =
        m_pPhysXManager->m_pkPhysXSDK->createScene(kNxSceneDesc);
    if (!pkNxScene && kNxSceneDesc.simType == NX_SIMULATION_HW)
    {
        kNxSceneDesc.simType = NX_SIMULATION_SW;
        pkNxScene =
            m_pPhysXManager->m_pkPhysXSDK->createScene(kNxSceneDesc);
        NiMessageBox::DisplayMessage(
            "Couldn't create hardware scene. Using Software.\n",
            "Scene Failure");
        bHaveHardware = false;
    }
    m_pPhysXManager->ReleaseSDKLock();
    
    if (!pkNxScene)
    {
        NiMessageBox::DisplayMessage(
            "Unable to create PhysX scene.\n",
            "Scene Failure");
        return false;
    }
    
    m_spPhysXScene->SetPhysXScene(pkNxScene);
            
    if (m_spPhysXScene)
    {
        m_spPhysXScene->SetUpdateDest(true);
        m_spPhysXScene->SetUpdateSrc(true);
        m_spPhysXScene->UpdateDestinations(0.0f, true);
		m_spPhysXScene->UpdateSources(0.0f, true);
    }
    
    return true;
}
//------------------------------------------------------------------------ 
/** 
 * 
 * Creates a screen texture
 */
void GameApp::CreateScreenPolygon(const char* imageFile,float fLeft, float fTop, float alpha)
{
	NiSourceTexture* pkTexture = NiSourceTexture::Create(NiApplication::ConvertMediaFilename(imageFile));
	// We want the screen texture to display within the safe zone, so we first get the safe
    // zone for the renderer 
    unsigned int uiWidth, uiHeight;
    NiRect<float> kSafeZone = m_spRenderer->GetSafeZone();
    m_spRenderer->ConvertFromNDCToPixels(kSafeZone.m_right, kSafeZone.m_bottom,
        uiWidth, uiHeight);

    NiScreenTexture* pkScreenTexture = NiNew NiScreenTexture(pkTexture);
	//pkScreenTexture->SetApplyMode(NiTexturingProperty::APPLY_DECAL);
    pkScreenTexture->AddNewScreenRect(fTop, uiWidth - fLeft - pkTexture->GetWidth(),
        pkTexture->GetWidth(), pkTexture->GetHeight(), 0, 0);

	

    GetScreenTextures().AddTail(pkScreenTexture);
	
	pkScreenTexture->SetApplyMode(NiTexturingProperty::APPLY_DECAL);
	pkScreenTexture->GetScreenRect(0).m_kColor.a = alpha;
}

//------------------------------------------------------------------------ 
/** 
 * 
 * Creates a screen texture
 */
void GameApp::ChangeAlphaOfHeadTexture(const char* imageFile,float fLeft, float fTop, float alpha)
{
	NiSourceTexture* pkTexture = NiSourceTexture::Create(NiApplication::ConvertMediaFilename(imageFile));
	// We want the screen texture to display within the safe zone, so we first get the safe
    // zone for the renderer 
    unsigned int uiWidth, uiHeight;
    NiRect<float> kSafeZone = m_spRenderer->GetSafeZone();
    m_spRenderer->ConvertFromNDCToPixels(kSafeZone.m_right, kSafeZone.m_bottom,
        uiWidth, uiHeight);

    NiScreenTexture* pkScreenTexture = NiNew NiScreenTexture(pkTexture);
    pkScreenTexture->AddNewScreenRect(fTop, uiWidth - fLeft - pkTexture->GetWidth(),
        pkTexture->GetWidth(), pkTexture->GetHeight(), 0, 0);

	NiTListIterator headTex = GetScreenTextures().GetHeadPos();
	//find the 4th texture = hackiness!!!
	if(GetScreenTextures().GetSize() > 3)
	{
		for(int i = 0; i <3; i++)
			headTex = GetScreenTextures().GetNextPos(headTex);
		
		GetScreenTextures().RemovePos(headTex);

		headTex = GetScreenTextures().GetHeadPos();
		for(int i = 0; i <2; i++)
			headTex = GetScreenTextures().GetNextPos(headTex);
		GetScreenTextures().InsertAfter(headTex,pkScreenTexture);
	}
	else
	{
		GetScreenTextures().AddTail(pkScreenTexture);
	}

	pkScreenTexture->SetApplyMode(NiTexturingProperty::APPLY_DECAL);
	pkScreenTexture->GetScreenRect(0).m_kColor.a = alpha;
}
//------------------------------------------------------------------------ 
/** 
 * 
 * Creates UI System
 * 
 * @return bool
 */
bool GameApp::CreateUISystem()
{	
    NiUIManager::Create();
    NiUIManager* pkUIManager = NiUIManager::GetUIManager();
    if (pkUIManager == NULL)
	  return false;

    if (!pkUIManager->Initialize(GetInputSystem(),
		NiSample::ConvertMediaFilename("Textures/UISkinFull.dds"), m_spCursor))
    {
	  return false;
    }

    m_fUIElementHeight = pkUIManager->GetMaxCharHeightInNSC() * 3.0f;
    m_fUIElementWidth = NiMin(0.40f, 
	  pkUIManager->GetMaxCharWidthInNSC() * 25.0f);
    m_fUIGroupHeaderHeight = pkUIManager->GetMaxCharHeightInNSC() * 2.75f;
    m_kUIElementGroupOffset.x = pkUIManager->GetMaxCharWidthInNSC() * 1.5f;
    m_kUIElementGroupOffset.y = pkUIManager->GetMaxCharHeightInNSC() * 0.5f +
	  m_fUIGroupHeaderHeight;

    if (m_bUseNavSystem)
    {
	  if (!NiNavManager::Create())
		return false;
    }

    NiUIManager::GetUIManager()->ReserveGamePadButton(
	  NiInputGamePad::NIGP_A, &m_kHideAll, NiUIManager::WASPRESSED);
    NiUIManager::GetUIManager()->ReserveKeyboardButton(
	  NiInputKeyboard::KEY_Z, &m_kHideAll, NiUIManager::WASPRESSED);

    return true;

	
}
//------------------------------------------------------------------------ 
/** 
 * 
 * Creates default cursor
 * 
 * @return bool
 */
bool GameApp::CreateCursor()
{
	NiRect<int> kRect;

	kRect.m_left = 0;
	kRect.m_top = 0;
	kRect.m_right = m_spRenderer->GetDefaultBackBuffer()->GetWidth();
	kRect.m_bottom = m_spRenderer->GetDefaultBackBuffer()->GetHeight();

	m_spCursor = NiSystemCursor::Create(m_spRenderer, kRect,
		NiCursor::IMMEDIATE, NiSystemCursor::STANDARD,
		NiSample::ConvertMediaFilename("textures/SystemCursors.tga"),m_spRenderer->GetDefaultRenderTargetGroup());
	m_spCursor->SetFlags(4);
	m_spCursor->SetPosition(0.0f, 512.0f, 371.0f);
	m_spCursor->Show(true);
	
	NIASSERT(m_spCursor);
	return true;


}
//------------------------------------------------------------------------ 
/** 
 * 
 * Overrides NiSample::CreateCamera (does nothing)
 * 
 * @return bool
 */
bool GameApp::CreateCamera()
{
	return true;
}
