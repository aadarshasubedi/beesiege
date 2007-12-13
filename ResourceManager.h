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
class GameCharacter;

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
		RES_MODEL_HEALERBEE,
		RES_MODEL_HONEYBEE,
		RES_MODEL_QUEEN,
		RES_MODEL_LOCUST,
		RES_MODEL_DRAGONFLY,
		RES_MODEL_BOSS,
		RES_MODEL_BASE,
		RES_MODEL_HEALTH,
		RES_MODEL_FLOWER,

		// fonts
		RES_FONT_SELECTEDSOLDIERS,

		// sounds
		RES_SOUND_AMBIENT,
		RES_SOUND_BEE,
		RES_SOUND_BEE_AWAITING,
		RES_SOUND_BEE_DYING,
		RES_SOUND_LOCUST,
		RES_SOUND_LOCUST_DYING,
		RES_SOUND_DRAGONFLY,
		RES_SOUND_DRAGONFLY_DYING,
		RES_SOUND_QUEEN,
		RES_SOUND_QUEEN_DYING,
		RES_SOUND_QUEEN_SOS
	};

	// initializes the manager
	bool Init(NiStream* stream, NiRenderer* renderer);
	
	// getters
	NiNodePropPtr GetNodeProp(ResourceType type);
	NiNodePtr GetNode(ResourceType type);
	NiFontPtr GetFont(ResourceType type);
	SoundPtr  GetSound(ResourceType type, GameCharacter* owner);
	
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
	bool LoadSound(ResourceType type, SoundDescPtr desc);

	// hash tables that contain our resources
	NiTMap<ResourceType , NiNodePropPtr> m_tResourcesModels; 
	NiTMap<ResourceType , NiFontPtr> m_tResourcesFonts;
	NiTMap<ResourceType, SoundDescPtr> m_tResourcesSounds;

	
};

#endif