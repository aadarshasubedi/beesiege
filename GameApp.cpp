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
#include <NiFogProperty.h>
#include <NiStandardAllocator.h>
#include <math.h>

#pragma comment(lib, "NiBinaryShaderLibDX9.lib")
#pragma comment(lib, "NiD3D10BinaryShaderLibD3D10.lib")
#pragma comment(lib, "NSBShaderLibDX9.lib")
#pragma comment(lib, "NSFParserLibDX9.lib")

//--------------------------------------------------------------------------- 
/** Creates a new NiApplication* 
 * 
 * @return NiApplication*
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
GameApp::GameApp() : NiApplication("BeeSiege",
    DEFAULT_WIDTH, DEFAULT_HEIGHT), m_fLastSimTime(0.0f)
{
	SetMediaPath("../../res/");
}
//---------------------------------------------------------------------- 
/** 
 * Initializes NiApplication
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

	return NiApplication::Initialize();
}
//---------------------------------------------------------------------- 
/** 
 * Creates the NiApplication's scene
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

	HidePointer();

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
        NiApplication::ConvertMediaFilename("models/final_again_1.nif"));
    
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
	
    return bSuccess;
}
//---------------------------------------------------------------------- 
/** 
 * Processes user input
 * 
 */
void GameApp::ProcessInput()
{
	NiApplication::ProcessInput();

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
    NiApplication::UpdateFrame();

	// Update all of our GameObj3ds
	GameManager::Get()->UpdateAll(m_fAccumTime);
	
	m_spScene->Update(m_fAccumTime);
	m_spScene->UpdateProperties();
	m_spScene->UpdateEffects();

	// Update the current listener position (for sound - FMOD)
	NxActor* queenActor = GameManager::Get()->GetQueen()->GetActor();
	NxVec3 nxPos = queenActor->getGlobalPosition()/50.0f;
	NxVec3 nxVel = queenActor->getLinearVelocity() / 50.0f;
	NxVec3 nxFor = queenActor->getGlobalOrientation().getColumn(0);
	
	
	SoundManager::Get()->Update(nxPos,
							    nxVel,
								NxVec3(0.0, 1.0, 0.0),nxFor);
	
	
    // Now we start the next step, giving a time that will actually be
    // in the past by the time we get the results.
    m_spPhysXScene->UpdateSources(m_fAccumTime);
	m_spCameraController->Update(m_fAccumTime);
	m_spPhysXScene->Simulate(m_fAccumTime);
    m_fLastSimTime = m_fAccumTime;	
}
//--------------------------------------------------------------------------- 
/** 
 * Renders HUD
 * 
 */
void GameApp::RenderScreenItems()
{
	NiApplication::RenderScreenItems();
	TextManager::Get()->DisplayText();
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
	NiApplication::Terminate();
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

