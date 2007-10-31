#include "ResourceManager.h"
#include "SoundManager.h"
#include <NiApplication.h>
#include <NiPhysX.h>
#include <NiCloningProcess.h>
#include <fstream>
using namespace std;

//------------------------------------------------------------------------
ResourceManager::ResourceManager() 
{
}
//------------------------------------------------------------------------
ResourceManager::~ResourceManager()
{
	//SoundManager::Destroy();
	m_tResourcesSounds.RemoveAll();
	m_tResourcesFonts.RemoveAll();
	m_tResourcesModels.RemoveAll();
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

	//bSuccess = SoundManager::Get()->Init();
	//if (!bSuccess) return false;

	//bSuccess = LoadSound(string("sounds/bee4.mp3"), 
	//RES_SOUND_BEE); 
	//if (!bSuccess) return false;


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
SoundPtr ResourceManager::GetSound(ResourceType type)
{
	SoundDescPtr soundDesc;
	if (m_tResourcesSounds.GetAt(type, soundDesc))
	{
		SoundPtr sound = SoundManager::Get()->CreateSound(soundDesc);
		return sound;
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
//------------------------------------------------------------------------
bool ResourceManager::LoadSound(const std::string& filename, ResourceType type)
{
	const char *convertedFilename = NiApplication::ConvertMediaFilename(filename.c_str());
	ifstream f;
	f.open(convertedFilename, ifstream::in);
	f.close();
	if (f.fail())
	{
		string err("Error sound: " + filename + " was not found");
		NiMessageBox(err.c_str(), "Error");
		return false;
	}

	SoundDescPtr desc = NiNew SoundDesc(convertedFilename);
	desc->mode = FMOD_LOOP_NORMAL | FMOD_3D | FMOD_HARDWARE;
	m_tResourcesSounds.SetAt(type, desc);
	return true;
}