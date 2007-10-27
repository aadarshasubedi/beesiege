#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

#include "SingletonObj.h"

class TiXmlElement;

class ConfigurationManager : public SingletonObj<ConfigurationManager>
{
	friend SingletonObj<ConfigurationManager>;
public:
	
	bool ReadConfigurationFile(const char* file);

	float agent_maxForce;
	float agent_maxTorque;
	float agent_maxVelocity;
	float agent_maxAngVel;
	float characterController_springConstant;
	float characterController_damping;
	float cameraController_distanceFromTarget;
	float cameraController_maxVelocity;
	float cameraController_damping;
	float cameraController_springConstant;
	float arrival_constant;
	float alignment_constant;
	float alignment_radius;
	float cohesion_constant;
	float cohesion_radius;
	float departure_constant;
	float separation_constant;
	float separation_radius;
	float wander_constant;
	float wander_noise;
	float bee_distanceFromTarget;
	float queen_speedGain;
	float queen_rotationGain;
	float queen_viewRadius;
	float timer_selectSoldiers;

private:

	ConfigurationManager();
	~ConfigurationManager();

	bool ReadFloat(float &value, TiXmlElement* node, const char* child);
	bool ReadControllers(TiXmlElement* node);
	bool ReadAgents(TiXmlElement* node);
	bool ReadCharacterController(TiXmlElement* node);
	bool ReadCameraController(TiXmlElement* node);
	bool ReadBehaviors(TiXmlElement* node);
	bool ReadArrival(TiXmlElement* node);
	bool ReadAlignment(TiXmlElement* node);
	bool ReadCohesion(TiXmlElement* node);
	bool ReadDeparture(TiXmlElement* node);
	bool ReadSeparation(TiXmlElement* node);
	bool ReadWander(TiXmlElement* node);
	bool ReadCharacters(TiXmlElement* node);
	bool ReadBee(TiXmlElement* node);
	bool ReadQueen(TiXmlElement* node);
	bool ReadTimers(TiXmlElement* node);
};

#endif