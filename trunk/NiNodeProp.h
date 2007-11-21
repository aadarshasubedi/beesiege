#ifndef NINODEPROP_H
#define NINODEPROP_H

#include "GameObj.h"
#include <NiNode.h>
#include <NiPhysXProp.h>

class NiNodeProp : public GameObj
{
public:

	// ctor / dtor
	NiNodeProp(NiNodePtr node, NiPhysXPropPtr prop) : 
	  m_spNode(node), m_spProp(prop)
	  {}
	~NiNodeProp()
	{
		m_spNode = 0;
		m_spProp = 0;
	}

	// NiNode, NiPhysXProp pair
	NiNodePtr       m_spNode;
	NiPhysXPropPtr  m_spProp;

private:
	
};

NiSmartPointer(NiNodeProp);
#endif