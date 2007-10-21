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
	friend class GameManager;
public:
	
	GameObj3d(ResourceManager::ResourceType type);
	virtual ~GameObj3d();

	inline NiNodePtr      GetNode() const { return m_spNode; } 
	inline NiPhysXPropPtr GetProp() const { return m_spProp; } 
protected:

	bool Init(NiNodePtr attachToThis);
	bool Init(NiNodePtr attachToThis, NiPhysXScenePtr attachToScene);
	void Update(float fTime);
	
	ResourceManager::ResourceType m_Type;
	NiNodePtr m_spNode;
	NiPhysXPropPtr m_spProp;
	NiPoint3  m_Pos;
	NiMatrix3 m_Rot;

private:
	virtual void DoExtraUpdates(float fTime) = 0;
	virtual bool DoExtraInits() = 0;
};

NiSmartPointer(GameObj3d);

#endif