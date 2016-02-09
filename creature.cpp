/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*
    creature data, creature logic
*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "Creature.h"

#include <fstream>
#include <vector>
#include <string>
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


int CreatureData::creatureID = 0;
int CreatureData::creatureCount = 0;


CreatureData::CreatureData() {
    CreatureData::creatureCount++;
    CreatureData::creatureID++;
}

CreatureData::CreatureData(std::string creaturename, size_t strength, size_t speed,
    size_t lifetime, std::vector<std::string> properties, std::string figurepath) {
    CreatureData::creatureCount++;
    CreatureData::creatureID++;
    this->creatureID = creatureCount;
    this->creaturename = creaturename;
    this->strength = strength;
    this->speed = speed;
    this->lifetime = lifetime;
    this->properties = properties;
    this->figurepath = figurepath;
}
