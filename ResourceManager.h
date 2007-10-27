#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "SingletonObj.h"
#include <string>
#include <NiStream.h>
#include <NiNode.h>
#include <NiTMap.h>
#include "NiNodeProp.h"
#include <NiFont.h>

class NiRenderer;

class ResourceManager : public SingletonObj<ResourceManager>
{
	friend SingletonObj<ResourceManager>;
public:
	
	enum ResourceType
	{
		// models
		RES_MODEL_BEE,
		RES_MODEL_QUEEN,
		RES_MODEL_LOCUST,
		RES_MODEL_ENEMY2,
		RES_MODEL_YELLOWBOX,

		// fonts
		RES_FONT_SELECTEDSOLDIERS
	};

	bool Init(NiStream* stream, NiRenderer* renderer);
	NiNodePropPtr GetNodeProp(ResourceType type);
	NiNodePtr GetNode(ResourceType type);
	NiFontPtr GetFont(ResourceType type);
	
private:
	ResourceManager();
	~ResourceManager();

	bool LoadNif(NiStream* stream, 
		         const std::string& filename,
				 ResourceType type);
	bool LoadFont(const std::string& filename, NiRenderer* renderer, ResourceType type);
	NiTMap<ResourceType , NiNodePropPtr> m_tResourcesModels; 
	NiTMap<ResourceType , NiFontPtr> m_tResourcesFonts;
};

#endif