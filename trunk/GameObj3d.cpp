#include "GameObj.h"
#include "GameObj3d.h"
#include <NiApplication.h>
#include "SingletonObj.h"
#include "ResourceManager.h"


//----------------------------------------------------------------------
GameObj3d::GameObj3d(ResourceManager::ResourceType type)
					   : m_Type(type),
						 m_spNode(0),
						 m_spProp(0),
						 m_Pos(NiPoint3(0.0, 0.0, 0.0)),
						 m_Rot(NiMatrix3())
{
}
//----------------------------------------------------------------------
GameObj3d::~GameObj3d()
{
	m_spNode = 0;
	m_spProp = 0;
}
//----------------------------------------------------------------------
bool GameObj3d::Init(NiNodePtr attachToThis)
{
    m_spNode = ResourceManager::Get()->GetNode(m_Type);
	if (m_spNode)
	{
		attachToThis->AttachChild(m_spNode);
		
		return DoExtraInits();
	}
	
	return false;
}
//----------------------------------------------------------------------
bool GameObj3d::Init(NiNodePtr attachToThis, NiPhysXScenePtr attachToScene)
{
	NiNodePropPtr nodeProp = ResourceManager::Get()->GetNodeProp(m_Type);
	if (nodeProp)
	{
		attachToThis->AttachChild(nodeProp->m_spNode);
		attachToScene->AddProp(nodeProp->m_spProp);

		m_spNode = nodeProp->m_spNode;
		m_spProp = nodeProp->m_spProp;
		
		return DoExtraInits();
	}
	return false;
}
//----------------------------------------------------------------------
void GameObj3d::Update(float fTime)
{
	DoExtraUpdates(fTime);
	
}
//----------------------------------------------------------------------