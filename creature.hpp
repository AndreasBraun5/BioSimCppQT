/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    All stuff regarding creatures encapsuled.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef INCLUDED_BIOSIM_CREATURE_HPP
#define INCLUDED_BIOSIM_CREATURE_HPP

#include <vector>
#include <string>


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class CreatureData /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
enum CreatureTileType{WATER, TERESTIAL, NONE};

// TODO Note: Maybe CreatureType is better. No, from this class there will be one that inherits
class Creature {

    //TODO Discuss: up till now every property is const. This will be a problem if I want to change the values.
    // The idea is to use the same creature objects in the selecting phase as I want to use if they are living
    // on the grid. So const is not possible.
public:	std::string creaturename; // const creature name then "operator =" function is unavailable in Creature.
    // TODO Discuss: the creature name equals the type of the creature
    size_t strength = 0;
    size_t speed = 0;
    size_t lifetime = 0;
    CreatureTileType creatureTileType;
    std::vector<std::string> properties;
    std::string figurepath;
    int positionX;
    int positionY;
    //void operator=(const CreatureData &b); // TODO Note: operator=, automatic generation is not working

    Creature() =  delete;
    Creature(const std::string &creaturename,
             size_t strength,
             size_t speed,
             size_t lifetime,
             const std::vector<std::string> &properties,
             const std::string &figurepath,
             CreatureTileType creatureTileType
             );
    void printCreatureDataToConsole() const;
};

#endif // CREATURE_HPP
