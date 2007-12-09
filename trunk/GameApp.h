#ifndef GAMEAPP_H
#define GAMEAPP_H

#undef NI_MEMORY_DEBUGGER

#include <NiSample.h>
#include <NiApplication.h>
#include <NiUIManager.h>
#include <NiPhysX.h>
#include "CameraController.h"

// Main Application
class GameApp : public NiSample
{
public:
	// ctor
    GameApp();
  
	// overloaded virtual functions inherited from
	// NiApplication
	// initializes the application
	bool Initialize();
	// creates the scene
	bool CreateScene();
	// processes input
	void ProcessInput();
	// updates one frame
	void UpdateFrame();
	// renders HUD
	void RenderScreenItems();
	// terminates the application
	void Terminate();
	// getters
	NiNodePtr       GetScene() const {return m_spScene;}
	NiPhysXScenePtr GetPhysXScene() const {return m_spPhysXScene;}
	NiCameraPtr     GetCamera() const {return m_spCamera;}
	CameraControllerPtr GetCameraController() const {return m_spCameraController;}

protected:
	// sets up the PhysX SDK parameters
	void SetPhysXSDKParams(const NxParameter kParam = NX_PARAMS_NUM_VALUES);
	// creates the PhysX scene
	bool CreatePhysXScene();

	// Pointer to the PhysX manager
	NiPhysXManager* m_pPhysXManager;
	// the PhysX scene
	NiPhysXScenePtr m_spPhysXScene;
	// a camera controller that positions and rotates
	// the camera accordingly
	CameraControllerPtr m_spCameraController;
	// last PhysX simulation time, required for correct PhysX simulation
	float m_fLastSimTime;

	// creates screen polygons
	void CreateScreenPolygon(const char* imageFile,float fLeft,float fTop);
	//Creates UI Elements
	virtual bool CreateUIElements();

};


#endif
