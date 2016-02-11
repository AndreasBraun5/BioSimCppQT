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


    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ variables /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
private: static int creatureCount;
public: int creatureID;
private:	std::string creaturename;
    size_t strength;
    size_t speed;
    size_t lifetime;
    std::vector<std::string> properties;
    std::string figurepath;


    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ constructors /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
public: CreatureData();    
public: CreatureData(std::string creaturename, size_t strength, size_t speed,
                     size_t lifetime, const std::vector<std::string> properties, std::string figurepath);


    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ methods /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
public: void printCreatureDataToConsole();
};

#endif /*!defined (INCLUDED_CREATURE_H)*/
