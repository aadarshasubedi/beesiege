#include <NiApplication.h>
#include "CameraController.h"
#include "VelocityController.h"
#include "Bee.h"
#include <NiPhysX.h>
#include "ConfigurationManager.h"
#include <fstream>
using namespace std;


//---------------------------------------------------------------------------
CameraController::CameraController(NiCameraPtr camera, NxActor* target) : 														 
 m_spCamera(camera),
 m_pTarget(target),
 m_fLastUpdate(0.0f),
 m_fDeltaTime(0.0f),
 m_vVelocity(0.0f, 0.0f, 0.0f),
 m_fcDistanceFromTarget(ConfigurationManager::Get()->cameraController_distanceFromTarget),
 m_fcMaxVelocity(ConfigurationManager::Get()->cameraController_maxVelocity),
 m_spVelController(NiNew VelocityController(ConfigurationManager::Get()->cameraController_damping, 
 ConfigurationManager::Get()->cameraController_springConstant, m_fcMaxVelocity))

{
    
}
//---------------------------------------------------------------------------
CameraController::~CameraController()
{
	m_spVelController = 0;
}

//---------------------------------------------------------------------------
void CameraController::Update(float fTime)
{
	m_fDeltaTime = (fTime - m_fLastUpdate) * 50.0f;
	m_fLastUpdate = fTime;
	
	if (m_pTarget)    
    {
        UpdatePositionAndOrientation();
    }

}

//---------------------------------------------------------------------------
void CameraController::UpdatePositionAndOrientation()
{    
	NxVec3 nxHeading;
	NxMat33 rot = m_pTarget->getGlobalOrientation();
	nxHeading = rot.getColumn(0);
	NiPoint3 heading(nxHeading.x, nxHeading.y, nxHeading.z);
	NxVec3 nxPos = m_pTarget->getGlobalPosition();
	NiPoint3 pos(nxPos.x, nxPos.y, nxPos.z);
	NiPoint3 targetPosition = pos - heading*m_fcDistanceFromTarget;
	
	NiPoint3 distance =  (targetPosition - m_spCamera->GetWorldTranslate());

	m_spVelController->Update(m_vVelocity, distance);
	NiPoint3 newPos = m_spCamera->GetTranslate() + m_vVelocity*m_fDeltaTime;
	m_spCamera->SetTranslate(newPos);
	
	NxVec3 nxUp = rot.getColumn(1);
	NiPoint3 up(nxUp.x, nxUp.y, nxUp.z);
	m_spCamera->LookAtWorldPoint(pos, up);
		
}
//---------------------------------------------------------------------------
