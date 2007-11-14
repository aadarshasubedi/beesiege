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
	
	GameObj3d(ResourceManager::ResourceType type);
	virtual ~GameObj3d();
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
	void SetEmmitance(const NiColor& color);
protected:

	bool Init(NiNodePtr attachToThis);
	bool Init(NiNodePtr attachToThis, NiPhysXScenePtr attachToScene);
	void Update(float fTime);

	ResourceManager::ResourceType m_Type;
	NiNodePtr m_spNode;
	NiPhysXPropPtr m_spProp;
	NiPoint3  m_Pos;
	NiMatrix3 m_Rot;
	bool m_bIsActive;

private:
	virtual void DoExtraUpdates(float fTime) = 0;
	virtual bool DoExtraInits() = 0;
	void SetEmmitanceForNode(NiAVObject* n, const NiColor& color);

};

NiSmartPointer(GameObj3d);

#endif