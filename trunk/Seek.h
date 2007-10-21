#ifndef SEEK_H_
#define SEEK_H_
// a comment
#include "Behavior.h"

class Seek : public Behavior
{
public:
	Seek();
	~Seek();

	// execute the behavior
	NxVec3 Execute(AgentInfoPtr aInfo);
};

NiSmartPointer(Seek);

#endif