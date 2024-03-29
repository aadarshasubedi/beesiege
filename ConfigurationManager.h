#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

#include "SingletonObj.h"

class TiXmlElement;

// Singleton Class
class ConfigurationManager : public SingletonObj<ConfigurationManager>
{
	friend SingletonObj<ConfigurationManager>;
public:
	
	// reads an XML configuration file
	bool ReadConfigurationFile(const char* file);
	
	// the constants that we need to read from the XML file
	// which are used by almost every class that has constant 
	// values
	float agent_maxForce;
	float agent_maxTorque;
	float agent_maxVelocity;
	float agent_maxAngVel;
	float agent_maxHeight;
	float characterController_springConstantForce;
	float characterController_dampingForce;
	float characterController_springConstantTorque;
	float characterController_dampingTorque;
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
	float bee_initialHealth;
	float bee_armorEffectiveDistance;
	float bee_armorCoefficient;
	float bee_damageEffectiveDistance;
	float bee_damageRadius;
	float bee_damage;
	float queen_speedGain;
	float queen_rotationGain;
	float queen_moveUpSpeedGain;
	float queen_viewRadius;
	float queen_maxHeight;
	float queen_fogScaleValue;
	float queen_initialHealth;
	float locust_initialHealth;
	float locust_viewRadius;
	float locust_damageRadius;
	float locust_damage;
	float dragonfly_initialHealth;
	float dragonfly_viewRadius;
	float dragonfly_damageRadius;
	float dragonfly_damage;
	float boss_initialHealth;
	float boss_viewRadius;
	float boss_damageRadius;
	float boss_damage;
	float healer_initialHealth;
	float healer_radius;
	float healer_duration;
	float healer_healAmount;
	float honeyBee_initialHealth;
	float honeyBee_duration;
	float honeyBee_gatherAmount;
	float timer_selectSoldiers;
	float scene_fogDefaultDepth;

private:
	
	// private ctor / dtor 
	ConfigurationManager();
	~ConfigurationManager();

	// functions that read certain nodes from the XML file
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
	bool ReadLocust(TiXmlElement* node);
	bool ReadDragonFly(TiXmlElement* node);
	bool ReadBoss(TiXmlElement* node);
	bool ReadHealer(TiXmlElement* node);
	bool ReadHoneyBee(TiXmlElement* node);
	bool ReadTimers(TiXmlElement* node);
	bool ReadScene(TiXmlElement* node);
};

#endif