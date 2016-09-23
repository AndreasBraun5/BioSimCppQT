/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    creature
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
// TODO Note: Maybe CreatureType is better.
class CreatureData {

private: static int creatureCount;

public:	const std::string creaturename;
    const size_t strength = 0;
    const size_t speed = 0;
    const size_t lifetime = 0;
    const std::vector<std::string> properties;
    const std::string figurepath;

    //void operator=(const CreatureData &b); // TODO Note: operator=, automatic generation is not working

    CreatureData() =  delete;
    CreatureData(const std::string &creaturename,
                 size_t strength,
                 size_t speed,
                 size_t lifetime,
                 const std::vector<std::string> &properties,
                 const std::string &figurepath);

    void printCreatureDataToConsole() const;
};

#endif // CREATURE_HPP
