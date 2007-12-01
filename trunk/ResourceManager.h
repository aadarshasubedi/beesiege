#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "SingletonObj.h"
#include <string>
#include <NiStream.h>
#include <NiNode.h>
#include <NiTMap.h>
#include "NiNodeProp.h"
#include <NiFont.h>
#include "Sound.h"

class NiRenderer;

// Singleton Class
class ResourceManager : public SingletonObj<ResourceManager>
{
	friend SingletonObj<ResourceManager>;
public:
	
	// all possible resource types
	enum ResourceType
	{
		// models
		RES_MODEL_BEE,
		RES_MODEL_QUEEN,
		RES_MODEL_LOCUST,
		RES_MODEL_ENEMY2,
		RES_MODEL_BASE,
		RES_MODEL_HEALTH,

		// fonts
		RES_FONT_SELECTEDSOLDIERS,

		// sounds
		RES_SOUND_BEE
	};

	// initializes the manager
	bool Init(NiStream* stream, NiRenderer* renderer);
	
	// getters
	NiNodePropPtr GetNodeProp(ResourceType type);
	NiNodePtr GetNode(ResourceType type);
	NiFontPtr GetFont(ResourceType type);
	SoundPtr  GetSound(ResourceType type);
	
private:
	// private ctor / dtor
	ResourceManager();
	~ResourceManager();

	// loads a NIF file
	bool LoadNif(NiStream* stream, 
		         const std::string& filename,
				 ResourceType type);
	// loads a font
	bool LoadFont(const std::string& filename, NiRenderer* renderer, ResourceType type);
	// loads a sound
	bool LoadSound(const std::string& filename, ResourceType type);

	// hash tables that contain our resources
	NiTMap<ResourceType , NiNodePropPtr> m_tResourcesModels; 
	NiTMap<ResourceType , NiFontPtr> m_tResourcesFonts;
	NiTMap<ResourceType, SoundDescPtr> m_tResourcesSounds;
};

#endif