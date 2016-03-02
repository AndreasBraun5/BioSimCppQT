/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    creature data, creature logic
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#if !defined (INCLUDED_CREATURE_H)
#define INCLUDED_CREATURE_H

#include <vector>
#include <string>

#include "Config.h"


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class CreatureData /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class CreatureData {
private: static int creatureCount;
public: int creatureID;
private:	std::string creaturename;
    size_t strength;
    size_t speed;
    size_t lifetime;
    std::vector<std::string> properties;
    std::string figurepath;

public: CreatureData();    
public: CreatureData(std::string creaturename, size_t strength, size_t speed,
                     size_t lifetime, const std::vector<std::string> properties, std::string figurepath);

public: void printCreatureDataToConsole();
    std::string getCreaturename() const;
    size_t getStrength() const;
    size_t getSpeed() const;
    std::vector<std::string> getProperties() const;
    size_t getLifetime() const;
};

#endif /*!defined (INCLUDED_CREATURE_H)*/
