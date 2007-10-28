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
    CameraController(NiCameraPtr camera, NxActor* target);
	~CameraController();
	void Update(float fTime);
	

private:
    
    void UpdatePositionAndOrientation();
	NiCameraPtr m_spCamera;
	NxActor* m_pTarget;
	float m_fLastUpdate;
	float m_fDeltaTime;
	NiPoint3  m_vVelocity;
	const float m_fcDistanceFromTarget;
	const float m_fcMaxVelocity;
	NiPoint3 m_vPosition;

	VelocityControllerPtr m_spVelController;
};


NiSmartPointer(CameraController);

#endif
