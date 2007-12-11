/**
 * Loads resources of any kind: models, sounds, fonts etc. Other 
 * objects refer to this manager to get resources. Singleton 
 * class. 
 */

#include "ResourceManager.h"
#include "SoundManager.h"
#include "GameCharacter.h"
#include <NiSample.h>
#include <NiPhysX.h>
#include <NiCloningProcess.h>
#include <fstream>
using namespace std;

#define ENABLE_SOUND

//------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
ResourceManager::ResourceManager() 
{
}
//------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
ResourceManager::~ResourceManager()
{
	SoundManager::Destroy();
	m_tResourcesSounds.RemoveAll();
	m_tResourcesFonts.RemoveAll();
	m_tResourcesModels.RemoveAll();
}
//------------------------------------------------------------------------ 
/** 
 * Initializes the manager
 * 
 * @param stream
 * @param renderer
 * 
 * @return bool
 */
bool ResourceManager::Init(NiStream* stream, NiRenderer* renderer)
{
	bool bSuccess = false;

	// load models
	bSuccess = LoadNif(stream, string("models/beefinal.nif"), RES_MODEL_BEE);
	if (!bSuccess) return false;
	bSuccess = LoadNif(stream, string("models/healer.nif"), RES_MODEL_HEALERBEE);
	if (!bSuccess) return false;
	bSuccess = LoadNif(stream, string("models/queenFinal.nif"), RES_MODEL_QUEEN);
	if (!bSuccess) return false;
	bSuccess = LoadNif(stream, string("models/locust_physx1.nif"), RES_MODEL_LOCUST);
	if (!bSuccess) return false;
	bSuccess = LoadNif(stream, string("models/yellowbox.nif"), RES_MODEL_BASE);
	if (!bSuccess) return false;
	bSuccess = LoadNif(stream, string("models/health.nif"), RES_MODEL_HEALTH);
	if (!bSuccess) return false;
	bSuccess = LoadNif(stream, string("models/flowers6.nif"),RES_MODEL_FLOWER);
	if (!bSuccess) return false;

	// load sounds
	bSuccess = SoundManager::Get()->Init();
#ifdef ENABLE_SOUND
	if (!bSuccess) return false;
	/////////////////////////////////////////////////////////////////////////////////
	bSuccess = LoadSound(RES_SOUND_BEE, NiNew 
		SoundDesc(NiSample::ConvertMediaFilename("sounds/bee4.mp3"), true, true)); 
	if (!bSuccess) return false;

	/////////////////////////////////////////////////////////////////////////////////
	bSuccess = LoadSound(RES_SOUND_BEE_AWAITING, NiNew 
		SoundDesc(NiSample::ConvertMediaFilename("sounds/beeAwaiting.mp3"), true, false));
	if (!bSuccess) return false;
	/////////////////////////////////////////////////////////////////////////////////
	bSuccess = LoadSound(RES_SOUND_BEE_DYING, NiNew 
		SoundDesc(NiApplication::ConvertMediaFilename("sounds/beeDying.mp3"), true, false));
	if (!bSuccess) return false;

	/////////////////////////////////////////////////////////////////////////////////
	bSuccess = LoadSound(RES_SOUND_LOCUST, NiNew
		SoundDesc(NiSample::ConvertMediaFilename("sounds/locust.mp3"), true, true));
	if (!bSuccess) return false;
	/////////////////////////////////////////////////////////////////////////////////
	bSuccess = LoadSound(RES_SOUND_LOCUST_DYING, NiNew 
		SoundDesc(NiSample::ConvertMediaFilename("sounds/locustDying.mp3"), true, false));
	if (!bSuccess) return false;
	/////////////////////////////////////////////////////////////////////////////////
	bSuccess = LoadSound(RES_SOUND_AMBIENT, NiNew 
		SoundDesc(NiSample::ConvertMediaFilename("sounds/ambient.mp3"), false, true));
	if (!bSuccess) return false;
#endif
	/////////////////////////////////////////////////////////////////////////////////

	// load fonts
	bSuccess = LoadFont(string("fonts/trebuchet.nff"), renderer, RES_FONT_SELECTEDSOLDIERS);
	if (!bSuccess) return false;

	return bSuccess;
	
}
//------------------------------------------------------------------------ 
/** 
 * Gets a node and a PhysX prop
 * 
 * @param type
 * 
 * @return NiNodePropPtr
 */
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
/** 
 * Gets a node with no PhysX props
 * 
 * @param type
 * 
 * @return NiNodePtr
 */
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
/** 
 * Gets a font
 * 
 * @param type
 * 
 * @return NiFontPtr
 */
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
/** 
 * Gets a sound
 * 
 * @param type
 * 
 * @return SoundPtr
 */
SoundPtr ResourceManager::GetSound(ResourceType type, GameCharacter* owner)
{
	SoundDescPtr soundDesc;
	if (m_tResourcesSounds.GetAt(type, soundDesc))
	{
		SoundPtr sound = SoundManager::Get()->CreateSound(soundDesc, owner);
		return sound;
	}
	
	return 0;
}
//------------------------------------------------------------------------ 
/** 
 * Loads a nif file
 * 
 * @param stream
 * @param filename
 * @param type
 * 
 * @return bool
 */
bool ResourceManager::LoadNif(NiStream* stream, 
							  const string& filename, 
							  ResourceType type)
{
	if (!stream) return false;

	bool bSuccess = stream->Load(
		NiSample::ConvertMediaFilename(filename.c_str()));
    
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
/** 
 * Loads a font
 * 
 * @param filename
 * @param renderer
 * @param type
 * 
 * @return bool
 */
bool ResourceManager::LoadFont(const std::string &filename, NiRenderer* renderer, 
							   ResourceType type)
{
	NiFontPtr font = NiFont::Create(renderer, 
		NiSample::ConvertMediaFilename(filename.c_str()));
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
/** 
 * Loads a sound
 * 
 * @param filename
 * @param type
 * 
 * @return bool
 */
bool ResourceManager::LoadSound(ResourceType type, SoundDescPtr desc)
{
	ifstream f;
	f.open(desc->filename.c_str(), ifstream::in);
	f.close();
	if (f.fail())
	{
		string err("Error sound: " + desc->filename + " was not found");
		NiMessageBox(err.c_str(), "Error");
		return false;
	}

	m_tResourcesSounds.SetAt(type, desc);
	return true;
}