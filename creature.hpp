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

// TODO: CreatureType
enum CreatureType{BIRNE, BUSCH, EICHE, EMU, GRAS, HUND, KAKTUS, KUH,
                  PFERD, SCHAF, SONNENBLUME, TANNE, TIGER, URSUS,

                  ALGEN, DELPHIN, FORELLE, HAI, KRABBE, PLANKTON,
                  SEETANG, WELS, CREATURE_TYPE_LENGTH};

enum CreatureTileType{WATER, TERESTIAL, NONE};

// TODO Note: Maybe CreatureType is better. No, from this class there will be one that inherits
class Creature {

    //TODO Discuss: up till now every property is const. This will be a problem if I want to change the values.
    // The idea is to use the same creature objects in the selecting phase as I want to use if they are living
    // on the grid. So const is not possible.
public:	std::string creaturename;
    size_t strength = 0;
    size_t speed = 0;
    size_t lifetime = 0;
    CreatureTileType creatureTileType;
    std::vector<std::string> properties;
    std::string figurepath;
    // TODO Discuss: Assigning each creature a CreatureType so that further comparisions must not be done via strcmp ?performance?
    CreatureType type;
    int positionX; // TODO: position
    int positionY;
    //void operator=(const CreatureData &b); // TODO Note: operator=, automatic generation is not working

    Creature() =  delete;
    Creature(const std::string &creaturename,
             size_t strength,
             size_t speed,
             size_t lifetime,
             const std::vector<std::string> &properties,
             const std::string &figurepath,
             // TODO: CreatureType
             CreatureType type
             );

    void printCreatureDataToConsole() const;
};

#endif // CREATURE_HPP
