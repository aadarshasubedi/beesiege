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
	m_tResourcesModels.RemoveAll();
	m_tResourcesFonts.RemoveAll();

}
//------------------------------------------------------------------------
bool ResourceManager::Init(NiStream* stream, NiRenderer* renderer)
{
	bool bSuccess = false;

	bSuccess = LoadNif(stream, string("models/bee2.nif"), RES_MODEL_BEE);
	if (!bSuccess) return false;
	bSuccess = LoadNif(stream, string("models/queen4.nif"), RES_MODEL_QUEEN);
	if (!bSuccess) return false;
	bSuccess = LoadNif(stream, string("models/enemy1.nif"), RES_MODEL_LOCUST);
	if (!bSuccess) return false;
	
	bSuccess = LoadFont(string("fonts/trebuchet.nff"), renderer, RES_FONT_SELECTEDSOLDIERS);
	if (!bSuccess) return false;

	return bSuccess;
	
}
//------------------------------------------------------------------------
NiNodePropPtr ResourceManager::GetNodeProp(ResourceType type)
{
	NiNodePropPtr nodeProp;
	if (m_tResourcesModels.GetAt(type, nodeProp))
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
	if (m_tResourcesModels.GetAt(type, nodeProp))
	{
		return (NiNode*)nodeProp->m_spNode->Clone();
	}
	
	return 0;
}
//------------------------------------------------------------------------
NiFontPtr ResourceManager::GetFont(ResourceType type)
{
	NiFontPtr font;
	if (m_tResourcesFonts.GetAt(type, font))
	{
		return font;
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
	for (unsigned int i=0; i<stream->GetObjectCount(); i++)
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
	m_tResourcesModels.SetAt(type, newNode);

	return true;
	
}
//------------------------------------------------------------------------
bool ResourceManager::LoadFont(const std::string &filename, NiRenderer* renderer, 
							   ResourceType type)
{
	NiFontPtr font = NiFont::Create(renderer, 
		NiApplication::ConvertMediaFilename(filename.c_str()));
	if (font)
	{
		m_tResourcesFonts.SetAt(type, font);
		return true;
	}
	else
	{
		string error(" could not be loaded");
		error = filename + error;
		NiMessageBox(error.c_str(), "NIF Error");
		return false;
	}
	
}