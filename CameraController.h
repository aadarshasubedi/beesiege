#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <NiTimeController.h>
#include <NxActor.h>
class NiApplication;

class VelocityController;
NiSmartPointer(VelocityController);
class GameObj3d;
NiSmartPointer(GameObj3d);

class CameraController : public NiTimeController 
{
    NiDeclareRTTI;

public:
    CameraController(NiCameraPtr camera, NxActor* target);
	~CameraController();
	void Update(float fTime);
	

private:
    bool TargetIsRequiredType () const;
    void UpdatePositionAndOrientation();
	NiCameraPtr m_spCamera;
	NxActor* m_pTarget;
	float m_fLastUpdate;
	float m_fDeltaTime;
	NiPoint3  m_vVelocity;
	const float m_fcDistanceFromTarget;
	const float m_fcMaxVelocity;

	VelocityControllerPtr m_spVelController;
};


NiSmartPointer(CameraController);

#endif
