/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    creature data
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
class CreatureData {
private: static int creatureCount;
public:	const std::string creaturename;
    const size_t strength = 0;
    const size_t speed = 0;
    const size_t lifetime = 0;
    const std::vector<std::string> properties;
    const std::string figurepath;

void operator=(const CreatureData &b); // TODO operator=, should be
public: CreatureData() =  delete;
public: CreatureData(std::string creaturename, size_t strength, size_t speed,
                     size_t lifetime, const std::vector<std::string> properties, std::string figurepath); // TODO const std::vector<std::string> &propierties

public: void printCreatureDataToConsole() const; // const here -> no membervariables changed
};

#endif // CREATURE_HPP
