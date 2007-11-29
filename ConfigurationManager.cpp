/**
 * Loads game constants from an XML file. Uses TinyXML for 
 * reading the XML file. Singleton class.
 */
#include "ConfigurationManager.h"
#include "tinyXML/tinyxml.h"

//------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
ConfigurationManager::ConfigurationManager()
{
}
//------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
ConfigurationManager::~ConfigurationManager()
{
}
//------------------------------------------------------------------------ 
/** 
 * Reads configuration file
 * 
 * @param file
 * 
 * @return bool
 */
bool ConfigurationManager::ReadConfigurationFile(const char *file)
{
	TiXmlDocument doc(file);
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		TiXmlElement* root = doc.RootElement();
		if (root)
		{
			if (!ReadControllers(root->FirstChildElement("controllers")))
				return false;
			if (!ReadBehaviors(root->FirstChildElement("behaviors")))
				return false;
			if (!ReadCharacters(root->FirstChildElement("characters")))
				return false;
			if (!ReadTimers(root->FirstChildElement("timers")))
				return false;
			if (!ReadScene(root->FirstChildElement("scene")))
				return false;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	
	return true;


}
//------------------------------------------------------------------------ 
/** 
 * Reads a flot value from an XML file
 * 
 * @param value
 * @param node
 * @param child
 * 
 * @return bool
 */
bool ConfigurationManager::ReadFloat(float &value, TiXmlElement* node, const char* child)
{
	TiXmlElement* current = node->FirstChildElement(child);
	if (current)
	{
		value    = (float)atof(current->GetText());
	}
	else 
	{
		return false;
	}

	return true;
}
//------------------------------------------------------------------------ 
/** 
 * Reads controllers
 * 
 * @param node
 * 
 * @return bool
 */
bool ConfigurationManager::ReadControllers(TiXmlElement* node)
{
	if (!node) return false;
	if (!ReadAgents(node->FirstChildElement("agent"))) 
		return false;
	if (!ReadCharacterController(node->FirstChildElement("characterController")))
		return false;
	if (!ReadCameraController(node->FirstChildElement("cameraController"))) 
		return false;

	return true;
	
}
//------------------------------------------------------------------------ 
/** 
 * Reads agents
 * 
 * @param node
 * 
 * @return bool
 */
bool ConfigurationManager::ReadAgents(TiXmlElement* node)
{
	if (!node) return false;

	if (ReadFloat(agent_maxForce, node, "maxForce") &&
		ReadFloat(agent_maxTorque, node, "maxTorque") &&
		ReadFloat(agent_maxVelocity, node, "maxVelocity") &&
		ReadFloat(agent_maxAngVel, node, "maxAngVel") &&
		ReadFloat(agent_maxHeight, node, "maxHeight")
		)
	{
		return true;
	}

	return false;
}
//------------------------------------------------------------------------ 
/** 
 * Reads a character controller
 * 
 * @param node
 * 
 * @return bool
 */
bool ConfigurationManager::ReadCharacterController(TiXmlElement* node)
{
	if (!node) return false;


	if (ReadFloat(characterController_springConstantForce, node, "springConstantForce") &&
		ReadFloat(characterController_dampingForce, node, "dampingForce") &&
		ReadFloat(characterController_springConstantTorque, node, "springConstantTorque") &&
		ReadFloat(characterController_dampingTorque, node, "dampingTorque")
		)
	{
		return true;
	}

	return false;
}
//------------------------------------------------------------------------ 
/** 
 * Reads a camera controller
 * 
 * @param node
 * 
 * @return bool
 */
bool ConfigurationManager::ReadCameraController(TiXmlElement* node)
{
	if (!node) return false;


	if (ReadFloat(cameraController_distanceFromTarget, node, "distanceFromTarget") &&
		ReadFloat(cameraController_maxVelocity, node, "maxVelocity") &&
		ReadFloat(cameraController_damping, node, "damping") &&
		ReadFloat(cameraController_springConstant, node, "springConstant") 
		)
	{
		return true;
	}

	return false;

}
//------------------------------------------------------------------------ 
/** 
 * Reads behaviors
 * 
 * @param node
 * 
 * @return bool
 */
bool ConfigurationManager::ReadBehaviors(TiXmlElement* node)
{
	if (!node) return false;

	if (!ReadArrival(node->FirstChildElement("arrival")))
		return false;
	
	if (!ReadAlignment(node->FirstChildElement("alignment")))
		return false;

	if (!ReadCohesion(node->FirstChildElement("cohesion")))
		return false;

	if (!ReadDeparture(node->FirstChildElement("departure")))
		return false;

	if (!ReadSeparation(node->FirstChildElement("separation")))
		return false;

	if (!ReadWander(node->FirstChildElement("wander")))
		return false;

	return true;
}
//------------------------------------------------------------------------ 
/** 
 * Reads Arrival
 * 
 * @param node
 * 
 * @return bool
 */
bool ConfigurationManager::ReadArrival(TiXmlElement* node)
{
	if (!node) return false;

	if (ReadFloat(arrival_constant, node, "constant"))
	{
		return true;
	}

	return false;
}
//------------------------------------------------------------------------ 
/** 
 * Reads Alignment
 * 
 * @param node
 * 
 * @return bool
 */ 
bool ConfigurationManager::ReadAlignment(TiXmlElement* node)
{
	if (!node) return false;

	if (ReadFloat(alignment_constant, node, "constant") &&
		ReadFloat(alignment_radius, node, "radius"))
	{
		return true;
	}

	return false;
}
//------------------------------------------------------------------------ 
/** 
 * Reads Cohesion
 * 
 * @param node
 * 
 * @return bool
 */ 
bool ConfigurationManager::ReadCohesion(TiXmlElement* node)
{
	if (!node) return false;

	if (ReadFloat(cohesion_constant, node, "constant") &&
		ReadFloat(cohesion_radius, node, "radius"))
	{
		return true;
	}

	return false;
}
//------------------------------------------------------------------------ 
/** 
 * Reads Departure
 * 
 * @param node
 * 
 * @return bool
 */ 
bool ConfigurationManager::ReadDeparture(TiXmlElement* node)
{
	if (!node) return false;

	if (ReadFloat(departure_constant, node, "constant"))
	{
		return true;
	}

	return false;
}
//------------------------------------------------------------------------ 
/** 
 * Reads Separation
 * 
 * @param node
 * 
 * @return bool
 */ 
bool ConfigurationManager::ReadSeparation(TiXmlElement* node)
{
	if (!node) return false;

	if (ReadFloat(separation_constant, node, "constant") &&
		ReadFloat(separation_radius, node, "radius"))
	{
		return true;
	}

	return false;
}
//------------------------------------------------------------------------ 
/** 
 * Reads Wander
 * 
 * @param node
 * 
 * @return bool
 */ 
bool ConfigurationManager::ReadWander(TiXmlElement* node)
{
	if (!node) return false;

	if (ReadFloat(wander_constant, node, "constant") &&
		ReadFloat(wander_noise, node, "noise"))
	{
		return true;
	}

	return false;
}
//------------------------------------------------------------------------ 
/** 
 * Reads Characters
 * 
 * @param node
 * 
 * @return bool
 */ 
bool ConfigurationManager::ReadCharacters(TiXmlElement* node)
{
	if (!node) return false;

	if (!ReadBee(node->FirstChildElement("bee")))
		return false;
	
	if (!ReadQueen(node->FirstChildElement("queen")))
		return false;

	return true;
}
//------------------------------------------------------------------------ 
/** 
 * Reads Bees
 * 
 * @param node
 * 
 * @return bool
 */ 
bool ConfigurationManager::ReadBee(TiXmlElement* node)
{
	if (!node) return false;

	if (ReadFloat(bee_distanceFromTarget, node, "distanceFromTarget"))
	{
		return true;
	}

	return false;
}
//------------------------------------------------------------------------ 
/** 
 * Reads Queen
 * 
 * @param node
 * 
 * @return bool
 */ 
bool ConfigurationManager::ReadQueen(TiXmlElement* node)
{
	if (!node) return false;

	if (ReadFloat(queen_speedGain, node, "speedGain") &&
		ReadFloat(queen_rotationGain, node, "rotationGain") &&
		ReadFloat(queen_moveUpSpeedGain, node, "moveUpSpeedGain") &&
		ReadFloat(queen_viewRadius, node, "viewRadius") &&
		ReadFloat(queen_maxHeight, node, "maxHeight") &&
		ReadFloat(queen_fogScaleValue, node, "fogScaleValue"))
	{
		return true;
	}

	return false;
}
//------------------------------------------------------------------------ 
/** 
 * Reads timers
 * 
 * @param node
 * 
 * @return bool
 */ 
bool ConfigurationManager::ReadTimers(TiXmlElement* node)
{
	if (!node) return false;

	if (ReadFloat(timer_selectSoldiers, node, "selectSoldiersTimer"))
	{
		return true;
	}

	return false;
}
//------------------------------------------------------------------------
/** 
 * Reads scene
 * 
 * @param node
 * 
 * @return bool
 */ 
bool ConfigurationManager::ReadScene(TiXmlElement* node)
{
	if (!node) return false;

	if (ReadFloat(scene_fogDefaultDepth, node, "fogDefaultDepth"))
	{
		return true;
	}

	return false;
}
//------------------------------------------------------------------------