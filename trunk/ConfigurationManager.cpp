#include "ConfigurationManager.h"
#include "tinyXML/tinyxml.h"

//------------------------------------------------------------------------
ConfigurationManager::ConfigurationManager()
{
}
//------------------------------------------------------------------------
ConfigurationManager::~ConfigurationManager()
{
}
//------------------------------------------------------------------------
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
bool ConfigurationManager::ReadAgents(TiXmlElement* node)
{
	if (!node) return false;

	if (ReadFloat(agent_maxForce, node, "maxForce") &&
		ReadFloat(agent_maxTorque, node, "maxTorque") &&
		ReadFloat(agent_maxVelocity, node, "maxVelocity") &&
		ReadFloat(agent_maxAngVel, node, "maxAngVel")
		)
	{
		return true;
	}

	return false;
}
//------------------------------------------------------------------------
bool ConfigurationManager::ReadCharacterController(TiXmlElement* node)
{
	if (!node) return false;


	if (ReadFloat(characterController_springConstant, node, "springConstant") &&
		ReadFloat(characterController_damping, node, "damping")
		)
	{
		return true;
	}

	return false;
}
//------------------------------------------------------------------------
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
bool ConfigurationManager::ReadQueen(TiXmlElement* node)
{
	if (!node) return false;

	if (ReadFloat(queen_speedGain, node, "speedGain") &&
		ReadFloat(queen_rotationGain, node, "rotationGain") &&
		ReadFloat(queen_moveUpSpeedGain, node, "moveUpSpeedGain") &&
		ReadFloat(queen_viewRadius, node, "viewRadius"))
	{
		return true;
	}

	return false;
}
//------------------------------------------------------------------------
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