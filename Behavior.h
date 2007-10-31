#ifndef _BEHAVIOR_H
#define _BEHAVIOR_H

#include "GameObj.h"

class NxVec3;
class AgentInfo;
NiSmartPointer(AgentInfo);

class Behavior : public GameObj
{
public:
	Behavior();
	virtual ~Behavior();

	// execute the behavior - ABSTRACT
	virtual NxVec3 Execute(AgentInfoPtr aInfo) = 0;

};

NiSmartPointer(Behavior);

#endif