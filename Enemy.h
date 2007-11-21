#ifndef ENEMY_H
#define ENEMY_H

#include "GameCharacter.h"

class Enemy : public GameCharacter
{
	NiDeclareRTTI;
public:
	Enemy(ResourceManager::ResourceType type);
	virtual ~Enemy();

protected:

	// extra updates and initializations
	virtual void DoExtraUpdates(float fTime) = 0;
	virtual bool DoExtraInits();


};

NiSmartPointer(Enemy);

#endif