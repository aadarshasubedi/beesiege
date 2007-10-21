#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "SingletonObj.h"
#include <string>
#include <NiStream.h>
#include <NiNode.h>
#include <NiTMap.h>
#include "NiNodeProp.h"

class ResourceManager : public SingletonObj<ResourceManager>
{
	friend SingletonObj<ResourceManager>;
public:
	
	enum ResourceType
	{
		RES_MODEL_BEE,
		RES_MODEL_QUEEN,
		RES_MODEL_ENEMY1,
		RES_MODEL_ENEMY2
	};

	bool Init(NiStream* stream);
	NiNodePropPtr GetNodeProp(ResourceType type);
	NiNodePtr GetNode(ResourceType type);
	
private:
	ResourceManager();
	~ResourceManager();

	bool LoadNif(NiStream* stream, 
		         const std::string& filename,
				 ResourceType type);
	bool LoadNifPhysX(NiStream* stream, 
					  NiNodePropPtr node);
	NiTMap<ResourceType , NiNodePropPtr> m_tResources; 
};

#endif