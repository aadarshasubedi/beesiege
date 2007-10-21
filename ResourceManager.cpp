#include "ResourceManager.h"
#include <NiApplication.h>
#include <NiPhysX.h>
#include <NiCloningProcess.h>
using namespace std;

//------------------------------------------------------------------------
ResourceManager::ResourceManager() 
{
}
//------------------------------------------------------------------------
ResourceManager::~ResourceManager()
{
	NiTMapIterator it = m_tResources.GetFirstPos();
	while(it)
	{
		NiNodePropPtr node;
		ResourceType type;
		m_tResources.GetNext(it, type, node);
		node = 0;

	}
	m_tResources.RemoveAll();

}
//------------------------------------------------------------------------
bool ResourceManager::Init(NiStream* stream)
{
	bool bSuccess = false;

	bSuccess = LoadNif(stream, string("bee.nif"), RES_MODEL_BEE);
	bSuccess = LoadNif(stream, string("queen.nif"), RES_MODEL_QUEEN);

	return bSuccess;
	
}
//------------------------------------------------------------------------
NiNodePropPtr ResourceManager::GetNodeProp(ResourceType type)
{
	NiNodePropPtr nodeProp;
	if (m_tResources.GetAt(type, nodeProp))
	{
		NiCloningProcess kCloning;
		
		NiNodePtr node = (NiNode*)nodeProp->m_spNode->Clone(kCloning);
		NiPhysXPropPtr prop = (NiPhysXProp*)nodeProp->m_spProp->Clone(kCloning);
		
		return NiNew NiNodeProp(node, prop);
	}
	
	return 0;
}
//------------------------------------------------------------------------
NiNodePtr ResourceManager::GetNode(ResourceType type)
{
	NiNodePropPtr nodeProp;
	if (m_tResources.GetAt(type, nodeProp))
	{
		return (NiNode*)nodeProp->m_spNode->Clone();
	}
	
	return 0;
}
//------------------------------------------------------------------------
bool ResourceManager::LoadNif(NiStream* stream, 
							  const string& filename, 
							  ResourceType type)
{
	if (!stream) return false;

	bool bSuccess = stream->Load(
		NiApplication::ConvertMediaFilename(filename.c_str()));
    
    if (!bSuccess)
    {
		string error(" could not be loaded");
		error = filename + error;
		NiMessageBox(error.c_str(), "NIF Error");
		return false;
    }

	NiNodePtr node = 0;
	NiPhysXPropPtr prop = 0;
	for (int i=0; i<stream->GetObjectCount(); i++)
	{
		NiObject* pkObject = 0;
		pkObject = stream->GetObjectAt(i);
		if (NiIsKindOf(NiPhysXProp, pkObject))
		{
			prop = (NiPhysXProp*)pkObject;
			prop->SetAllDestInterp(true);
            prop->SetAllSrcInterp(true);
			
		}
		else if (NiIsKindOf(NiNode, pkObject))
		{
			node = (NiNode*)pkObject;
		}
	}
	
	NiNodePropPtr newNode = NiNew NiNodeProp(node, prop);
	m_tResources.SetAt(type, newNode);

	return true;
	
}
