/**
 * A GameObj with 3d attributes
 */
#include "GameObj3d.h"
#include "ResourceManager.h"
#include <NiApplication.h>
#include <NiFogProperty.h>

//----------------------------------------------------------------------
// implements RTTI
NiImplementRTTI(GameObj3d, GameObj);
//----------------------------------------------------------------------
/** 
 * Ctor
 * 
 * @param type
 */
GameObj3d::GameObj3d(ResourceManager::ResourceType type)
					   : m_Type(type),
						 m_spNode(0),
						 m_spProp(0),
						 m_Pos(NiPoint3(0.0, 0.0, 0.0)),
						 m_Rot(NiMatrix3()),
						 m_bIsActive(true)
{
}
//---------------------------------------------------------------------- 
/** 
 * Dtor
 * 
 */
GameObj3d::~GameObj3d()
{
	m_spNode = 0;
	m_spProp = 0;
}
//---------------------------------------------------------------------- 
/** 
 * Initializes the 3d Object
 * 
 * @param attachToThis
 * 
 * @return bool
 */
bool GameObj3d::Init(NiNodePtr attachToThis)
{
	// get a 3d model from the ResourceManager depending on the
	// object's type
    m_spNode = ResourceManager::Get()->GetNode(m_Type);
	if (m_spNode)
	{
		// attach the model to the scene graph
		if (attachToThis)
			attachToThis->AttachChild(m_spNode);

		// do any extra inits (virtual)
		return DoExtraInits();
	}
	
	return false;
}
//---------------------------------------------------------------------- 
/** 
 * Initializes the 3d Object with PhysX attributes
 * 
 * @param attachToThis
 * @param attachToScene
 * 
 * @return bool
 */
bool GameObj3d::Init(NiNodePtr attachToThis, NiPhysXScenePtr attachToScene)
{
	// get a 3d model and a PhysX prop from the ResourceManager
	// depending on the object's type
	NiNodePropPtr nodeProp = ResourceManager::Get()->GetNodeProp(m_Type);
	if (nodeProp)
	{
		m_spNode = nodeProp->m_spNode;
		m_spProp = nodeProp->m_spProp;

		// attach the model to the scene graph
		if (attachToThis)
			attachToThis->AttachChild(m_spNode);
		
		// attach the PhysX prop to the main PhysX scene
		if (attachToScene)
			attachToScene->AddProp(m_spProp);

		// do extra initializations
		return DoExtraInits();
	}
	return false;
}
//---------------------------------------------------------------------- 
/** 
 * Updates the object's attributes
 * 
 * @param fTime
 */
void GameObj3d::Update(float fTime)
{
	DoExtraUpdates(fTime);
	if (m_spNode)
	{
		m_spNode->UpdateProperties();
		m_spNode->UpdateEffects();
		m_spNode->Update(fTime);
	}
}
//---------------------------------------------------------------------- 
/** 
 * Changes the object's emmisive color
 * 
 * @param color
 */
void GameObj3d::SetEmmitance(const NiColor& color)
{
	SetEmmitanceForNode(m_spNode, color);
}
//---------------------------------------------------------------------- 
/** 
 * The recursive function that does all the work, in order to 
 * change the object's emmisive color 
 * 
 * @param n
 * @param color
 */
void GameObj3d::SetEmmitanceForNode(NiAVObject* n, const NiColor& color)
{
	// traverse the object's node and change the emmisive color
	NiNodePtr node = 0;
	NiGeometryPtr geom = 0;
	if (NiIsKindOf(NiNode, n))
	{
		node = (NiNode*)n;
		NiMaterialPropertyPtr mat = (NiMaterialProperty*)node->GetProperty(NiProperty::MATERIAL);
		if (mat)
			mat->NiMaterialProperty::SetEmittance(color);
		for (int i=0; i<node->GetChildCount(); i++)
		{
			SetEmmitanceForNode(node->GetAt(i), color);
		}
	}
	else if (NiIsKindOf(NiGeometry, n))
	{
		geom = (NiGeometry*)n;
		NiMaterialPropertyPtr mat = (NiMaterialProperty*)geom->GetProperty(NiProperty::MATERIAL);
		if (mat)
			mat->NiMaterialProperty::SetEmittance(color);
	}
}

