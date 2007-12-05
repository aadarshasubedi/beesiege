/**
* This is a flower class which keeps flowers randomly in the scene 
* so that they act as a source to generate honey for the honey bees.
*/

#include "Flower.h"
#include "GameManager.h"

//--------------------------------------------------------------
NiImplementRTTI(Flower, GameObj3d);
//--------------------------------------------------------------

/**
* Constructor
*/
Flower::Flower() :
GameObj3d(ResourceManager::RES_MODEL_FLOWER)
{
}
//--------------------------------------------------------------

/**
* Destructor
*/
Flower::~Flower()
{
}
//--------------------------------------------------------------

void Flower::DoExtraUpdates(float fTime)
{
}

//--------------------------------------------------------------
bool Flower::DoExtraInits()
{
	return true;
}
