/**
 * Controlls the camera using a mass-spring system. The camera 
 * always follows the target (player). 
 */

#include <NiApplication.h>
#include <NiPhysX.h>
#include <NiViewMath.h>
#include "CameraController.h"
#include "VelocityController.h"
#include "Bee.h"
#include "ConfigurationManager.h"
#include <fstream>
#include <math.h>

//---------------------------------------------------------------------------
/** 
 * The constructor
 * 
 * @param camera
 */
CameraController::CameraController(NiCameraPtr camera) : 														 
 m_spCamera(camera),
 m_fLastUpdate(0.0f),
 m_fDeltaTime(0.0f),
 m_vVelocity(0.0f, 0.0f, 0.0f),
 m_fcDistanceFromTarget(ConfigurationManager::Get()->cameraController_distanceFromTarget),
 m_fcMaxVelocity(ConfigurationManager::Get()->cameraController_maxVelocity),
 m_vPosition(0.0, 0.0, 0.0),
 m_vTarget(0.0, 0.0, 0.0),
 m_vTargetVel(0.0, 0.0, 0.0),
 m_fRotateZ(0.0f),
 m_fRotateY(0.0f),
 m_bIsRotating(false),
 m_spVelController(NiNew VelocityController(ConfigurationManager::Get()->cameraController_damping, 
 ConfigurationManager::Get()->cameraController_springConstant, m_fcMaxVelocity))

{
    
}
//---------------------------------------------------------------------------
/** 
 * The destructor
 * 
 */
CameraController::~CameraController()
{
	m_spVelController = 0;
}

//--------------------------------------------------------------------------- 
/** 
 * Updates the camera's position
 * 
 * @param fTime
 */
void CameraController::Update(float fTime)
{
	m_fDeltaTime = (fTime - m_fLastUpdate) * 50.0f;
	m_fLastUpdate = fTime;
	
	UpdatePositionAndOrientation();
    

}
//---------------------------------------------------------------------------
/** 
 * Rotates the view by dx on the Y axis and dy on the Z axis
 * 
 * @param dx
 * @param dy
 */
void CameraController::RotateCamera(float dx, float dy)
{
	if (!m_bIsRotating) m_bIsRotating = true;

	m_fRotateZ += dy*0.01;
	m_fRotateY += dx*0.01;

	if (m_fRotateZ >= 1.56) 
		m_fRotateZ = 1.56f;
	else if (m_fRotateZ <= -1.56) 
		m_fRotateZ = -1.56f;

	NiMatrix3 rotation =  m_spCamera->GetParent()->GetWorldRotate();
	NiMatrix3 newRot;
	newRot.FromEulerAnglesYZX(m_fRotateY,m_fRotateZ,0.0);
	rotation = newRot*rotation;
	NiPoint3 heading;
	rotation.GetCol(0, heading);
	m_vTarget = m_spCamera->GetParent()->GetWorldTranslate() - heading*m_fcDistanceFromTarget;
	
}
//--------------------------------------------------------------------------- 
/** 
 * Stops the rotation of the camera
 * 
 */
void CameraController::StopRotateCamera()
{
	m_bIsRotating = false;
	m_fRotateZ = 0.0f;
	m_fRotateY = 0.0f;
}
//--------------------------------------------------------------------------- 
/** 
 * Updates the position and orientation of the camera
 * 
 */
void CameraController::UpdatePositionAndOrientation()
{    
	// get the camera's parent node
	NiNodePtr m_spTarget = m_spCamera->GetParent();
	// get the parent's rotation matrix
	NiMatrix3 rotation = m_spTarget->GetWorldRotate();
	// find the local heading vector
	NiPoint3 heading;
	rotation.GetCol(0, heading);
	// position the target behind the parent
	NiPoint3 targetPosition = m_spTarget->GetWorldTranslate() - heading*m_fcDistanceFromTarget;

	// if the camera is not rotated by user input then update the
	// current target
	if (!m_bIsRotating) 
	{
		m_vTarget = targetPosition;
	}

	// find the distance between the target and the camera
	NiPoint3 distance =  (m_vTarget - m_vPosition);
	// update the camera's velocity using a mass-spring controller
	m_spVelController->Update(m_vVelocity, distance);
	// integrate position
	m_vPosition = m_vPosition + m_vVelocity * m_fDeltaTime;
	// set new position
	m_spCamera->SetWorldTranslate(m_vPosition);
	// set orientation (look at parent)
	NiMatrix3 newRotation = NiViewMath::LookAt(m_spTarget->GetWorldTranslate(), m_vPosition, NiPoint3(0.0, 1.0, 0.0));
	m_spCamera->SetWorldRotate(newRotation);		
}
//---------------------------------------------------------------------------
