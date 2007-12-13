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

	//typedef struct queueElement
	//{
	//	int   i;
	//	float f;
	//}element;

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
	NiTPointerList<int> beeTypesQueue;
	NiTPointerList<float> beeTimeQueue;	
	bool hasQueueChanged;
	bool hasAlphaChanged;
	float alphaValue;
	float initialQueueOffset;

protected:
	// sets up the PhysX SDK parameters
	void SetPhysXSDKParams(const NxParameter kParam = NX_PARAMS_NUM_VALUES);
	// creates the PhysX scene
	bool CreatePhysXScene();
	// creates screen polygons
	void CreateScreenPolygon(const char* imageFile,float fLeft,float fTop, float alpha);
	void ChangeAlphaOfHeadTexture(const char* imageFile,float fLeft, float fTop, float alpha);
	//Creates UI Elements
	bool CreateUIElements();
	// Creates UI System
	bool CreateUISystem();
	// Creates default cursor
	bool CreateCursor();
	// Overrides NiSample::CreateCamera (does nothing)
	bool CreateCamera();

	void UpdateBeeQueue();
	void CreateBees();

	// Pointer to the PhysX manager
	NiPhysXManager* m_pPhysXManager;
	// the PhysX scene
	NiPhysXScenePtr m_spPhysXScene;
	// a camera controller that positions and rotates
	// the camera accordingly
	CameraControllerPtr m_spCameraController;
	// last PhysX simulation time, required for correct PhysX simulation
	float m_fLastSimTime;

};


#endif
