#ifndef CAMERACONTROLLER2_H
#define CAMERACONTROLLER2_H

#include <NxActor.h>
#include "GameObj.h"

class VelocityController;
NiSmartPointer(VelocityController);
class GameObj3d;
NiSmartPointer(GameObj3d);

class CameraController : public GameObj
{
  
public:
	// ctor / dtor
    CameraController(NiCameraPtr camera);
	~CameraController();

	// updates the camera
	void Update(float fTime);
	// manually rotates the camera
	void RotateCamera(float dx, float dy);
	// signals end of manual rotation
	void StopRotateCamera();
	// getters
	inline NiPoint3 GetVelocity() const {return m_vVelocity;}
private:
    
	// updates camera position and orientation
    void UpdatePositionAndOrientation();

	// pointer to the camera
	NiCameraPtr m_spCamera;
	// last update time
	float m_fLastUpdate;
	// delta time
	float m_fDeltaTime;
	// desired distance from target
	const float m_fcDistanceFromTarget;
	// max velocity
	const float m_fcMaxVelocity;
	// camera velocity
	NiPoint3  m_vVelocity;
	// camera position
	NiPoint3 m_vPosition;
	// target position
	NiPoint3 m_vTarget;
	// target velocity
	NiPoint3 m_vTargetVel;
	// new rotation matrix for updating
	NiMatrix3 m_mNewRotation;
	// rotation values
	float m_fRotateZ;
	float m_fRotateY;
	// is the camera rotated manually
	bool  m_bIsRotating;
	// a velocity controller that is used to smoothly 
	// change the velocity of the camera
	VelocityControllerPtr m_spVelController;
};


NiSmartPointer(CameraController);

#endif
