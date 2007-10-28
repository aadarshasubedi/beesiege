#ifndef GAMEAPP_H
#define GAMEAPP_H

#include <NiApplication.h>
#include <NiPhysX.h>
#include "CameraController.h"

class GameApp : public NiApplication
{
public:
    GameApp();
  
	bool Initialize();
	bool CreateScene();
	void ProcessInput();
	void UpdateFrame();
	void RenderScreenItems();
	void Terminate();

	inline NiNodePtr       GetScene() const {return m_spScene;}
	inline NiPhysXScenePtr GetPhysXScene() const {return m_spPhysXScene;}
	inline NiCameraPtr     GetCamera() const {return m_spCamera;}

protected:
	
	

	void SetPhysXSDKParams(const NxParameter kParam = NX_PARAMS_NUM_VALUES);
	bool CreatePhysXScene();
	
	NiPhysXManager* m_pPhysXManager;
	NiPhysXScenePtr m_spPhysXScene;
	CameraControllerPtr m_spCameraController;
	float m_fLastSimTime;
	
};


#endif