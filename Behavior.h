#ifndef _BEHAVIOR_H
#define _BEHAVIOR_H

#include "GameObj.h"

#include <string>

class NxVec3;
class AgentInfo;
NiSmartPointer(AgentInfo);

class Behavior : public GameObj
{
public:
	Behavior(const std::string& type);
	virtual ~Behavior();

	// execute the behavior - ABSTRACT
	virtual NxVec3 Execute(AgentInfoPtr aInfo) = 0;

	inline const std::string GetType() const { return m_sType; }

protected:

	const std::string m_sType;
};

NiSmartPointer(Behavior);

#endif