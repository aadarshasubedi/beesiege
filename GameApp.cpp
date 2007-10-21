#include "GameApp.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "CameraController.h"
#include "InputManager.h"

#pragma comment(lib, "NiBinaryShaderLibDX9.lib")
#pragma comment(lib, "NiD3D10BinaryShaderLibD3D10.lib")
#pragma comment(lib, "NSBShaderLibDX9.lib")
#pragma comment(lib, "NSFParserLibDX9.lib")


//---------------------------------------------------------------------------
NiApplication* NiApplication::Create()
{
    return NiNew GameApp;
}
//---------------------------------------------------------------------------
GameApp::GameApp() : NiApplication("BeeSiege",
    DEFAULT_WIDTH, DEFAULT_HEIGHT, true)
{
	SetMediaPath("../../res/models/");
}
//----------------------------------------------------------------------
bool GameApp::Initialize()
{
	m_pPhysXManager = NiPhysXManager::GetPhysXManager();
	if (!m_pPhysXManager->Initialize())
        return false;
    SetPhysXSDKParams();

	return NiApplication::Initialize();
}
//----------------------------------------------------------------------
bool GameApp::CreateScene()
{
	// Because our scene will have some billboards with alpha, we use 
    // a NiAlphaAccumulator in order that our alpha gets sorted and drawn
    // correctly.5
    NiAlphaAccumulator* pkAccum = NiNew NiAlphaAccumulator;
    m_spRenderer->SetSorter(pkAccum);
	m_spRenderer->SetBackgroundColor(NiColor(0.0, 0.0, 1.0));

    NiStream kStream;

    // Load in the scenegraph for our world...
    bool bSuccess = kStream.Load(
        NiApplication::ConvertMediaFilename("scene.nif"));
    
    if (!bSuccess)
    {
        NiMessageBox("WORLD.NIF file could not be loaded!", "NIF Error");
        return false;
    }

    m_spScene = (NiNode*) kStream.GetObjectAt(0);
    NIASSERT(NiIsKindOf(NiNode, m_spScene));

	// We expect the world to have been exported with a camera, so we 
    // look for it here.
    m_spCamera = FindFirstCamera(m_spScene);
    if (!m_spCamera)
    {
        NiMessageBox("The NIF file has no camera!", "Camera Error");
        return false;
    }
	
	SetMaxFrameRate(120.0f);

	HidePointer();

	m_spScene->UpdateProperties();
	m_spScene->UpdateEffects();

	if (!CreatePhysXScene())
	{
		return false;
	}

	bSuccess = ResourceManager::Get()->Init(&kStream);
	if (!bSuccess) return false;

	bSuccess = GameManager::Get()->Init(m_spScene, m_spPhysXScene);
	if (!bSuccess) return false;
	
	CameraControllerPtr pkCameraController = NiNew CameraController(m_spCamera, 
		GameManager::Get()->GetQueen()->GetAgent()->GetActor());
	pkCameraController->SetTarget(GameManager::Get()->GetQueen()->GetNode());

	
    return bSuccess;
}
//----------------------------------------------------------------------
void GameApp::ProcessInput()
{
	NiApplication::ProcessInput();

	if (GetInputSystem())
	{
		InputManager::Get()->ProcessInput(GetInputSystem(), this);
	}
	
}
//---------------------------------------------------------------------
void GameApp::UpdateFrame()
{
	// update everything
	NiApplication::UpdateFrame();

	// Update physics
    if (m_spPhysXScene)
    {
        m_spPhysXScene->UpdateSources(m_fAccumTime);
        if (m_spPhysXScene->Simulate(m_fAccumTime))
        {
            m_spPhysXScene->FetchResults(m_fAccumTime, true);
            m_spPhysXScene->UpdateDestinations(m_fAccumTime);
        }
    }

	GameManager::Get()->UpdateAll(m_fAccumTime);
	m_spScene->Update(m_fAccumTime);
	m_spScene->UpdateProperties();
	m_spScene->UpdateEffects();
	
	
}
//---------------------------------------------------------------------
void GameApp::Terminate()
{

	m_spPhysXScene = 0;
	GameManager::Destroy();
	ResourceManager::Destroy();
	InputManager::Destroy();
	NiApplication::Terminate();
	if (m_pPhysXManager)
        m_pPhysXManager->Shutdown();
}
//------------------------------------------------------------------------
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