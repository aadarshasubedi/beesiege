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
    CameraController(NiCameraPtr camera);
	~CameraController();
	void Update(float fTime);
	void RotateCamera(float dx, float dy);
	void StopRotateCamera();
	inline NiPoint3 GetVelocity() const {return m_vVelocity;}
private:
    
	void UpdateTargetPosition(const NiPoint3& target);
    void UpdatePositionAndOrientation();
	NiCameraPtr m_spCamera;
	float m_fLastUpdate;
	float m_fDeltaTime;
	NiPoint3  m_vVelocity;
	const float m_fcDistanceFromTarget;
	const float m_fcMaxVelocity;
	NiPoint3 m_vPosition;
	NiPoint3 m_vTarget;
	NiPoint3 m_vTargetVel;
	float m_fRotateZ;
	float m_fRotateY;
	bool  m_bIsRotating;
	VelocityControllerPtr m_spVelController;
};


NiSmartPointer(CameraController);

#endif
