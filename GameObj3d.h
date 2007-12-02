#ifndef GAMEOBJ3D_H
#define GAMEOBJ3D_H

#include "GameObj.h"
#include <NiNode.h>
#include <NiPoint3.h>
#include <NiMatrix3.h>
#include <NiPhysXScene.h>
#include <NiPhysXProp.h>
#include "ResourceManager.h"

class GameObj3d : public GameObj
{
	NiDeclareRTTI;

	friend class GameManager;
public:
	
	// ctor / dtor
	GameObj3d(ResourceManager::ResourceType type);
	virtual ~GameObj3d();

	// getters / setters
	NiNodePtr GetNode() const 
	{
		return m_spNode;
	} 
	NiPhysXPropPtr GetProp() const 
	{
		return m_spProp; 
	}
	const ResourceManager::ResourceType GetType() const
	{
		return m_Type;
	}
	const bool IsActive() const 
	{
		return m_bIsActive;
	}
	void SetActive (bool value)
	{
		m_bIsActive = value;
	}
	

	// changes the emmisive color of a NiNode
	void SetEmmitance(const NiColor& color);

protected:

	// initilizes the object and attaches it to a parent
	// node in the scene graph
	bool Init(NiNodePtr attachToThis);
	// overloaded function that also attaches PhysX content to the
	// main PhysX scene
	bool Init(NiNodePtr attachToThis, NiPhysXScenePtr attachToScene);
	// updates the object
	void Update(float fTime);
	// recursive function that sets the emmisive color of a node
	void SetEmmitanceForNode(NiAVObject* n, const NiColor& color);

	// object type
	ResourceManager::ResourceType m_Type;
	// NiNode for rendering the object's model
	NiNodePtr m_spNode;
	// NiPhysXProp that contains PhysX information for
	// simulating the object
	NiPhysXPropPtr m_spProp;
	// object's position
	NiPoint3  m_Pos;
	// object's rotation
	NiMatrix3 m_Rot;
	// is the object active or should it be removed
	bool m_bIsActive;

private:
	// extra updates and initializations
	virtual void DoExtraUpdates(float fTime) = 0;
	virtual bool DoExtraInits() = 0;

};

NiSmartPointer(GameObj3d);

#endif