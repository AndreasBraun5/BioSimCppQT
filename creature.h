/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*
    creature data, creature logic
 */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#pragma once
#if !defined (INCLUDED_CREATURE_H)
#define INCLUDED_CREATURE_H

#include <vector>
#include <string>

#include "Config.h"
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
class CreatureData {

private: static int creatureCount;
private: static	int creatureID;

public:	std::string creaturename;
public:	size_t strength;
public:	size_t speed;
public:	size_t lifetime;
public:	std::vector<std::string> properties;
public:	std::string figurepath;

public: CreatureData();

public: CreatureData(std::string creaturename, size_t strength, size_t speed,
    size_t lifetime, std::vector<std::string> properties, std::string figurepath);
};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#endif /*!defined (INCLUDED_CREATURE_H)*/
