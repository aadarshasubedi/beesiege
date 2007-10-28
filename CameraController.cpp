#include <NiApplication.h>
#include "CameraController.h"
#include "VelocityController.h"
#include "Bee.h"
#include <NiPhysX.h>
#include <NiViewMath.h>
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
 ConfigurationManager::Get()->cameraController_springConstant, m_fcMaxVelocity)),
 m_vPosition(0.0, 0.0, 0.0)

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
	NiNodePtr m_spTarget = m_spCamera->GetParent();
	NiMatrix3 rotation = m_spTarget->GetWorldRotate();
	NiPoint3 heading;
	rotation.GetCol(0, heading);
	NiPoint3 targetPosition = m_spTarget->GetWorldTranslate() - heading*m_fcDistanceFromTarget;
	NiPoint3 distance =  (targetPosition - m_vPosition);
	m_spVelController->Update(m_vVelocity, distance);
	m_vPosition = m_vPosition + m_vVelocity * m_fDeltaTime;
	m_spCamera->SetWorldTranslate(m_vPosition);
	NiMatrix3 rot;
	rot.MakeIdentity();
	m_spCamera->SetWorldRotate(rot);
	NiMatrix3 newRotation = NiViewMath::LookAt(m_spTarget->GetWorldTranslate(), m_vPosition, NiPoint3(0.0, 1.0, 0.0));
	m_spCamera->SetWorldRotate(newRotation);
	//m_spCamera->LookAtWorldPoint(m_spTarget->GetWorldTranslate(), NiPoint3(0.0, 1.0, 0.0));
		
}
//---------------------------------------------------------------------------
