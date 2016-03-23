/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    creature data
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "creature.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
int CreatureData::creatureCount = 0;


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class CreatureData /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
void CreatureData::operator=(const CreatureData &cd){} // TODO operator=

CreatureData::CreatureData(std::string creaturename, size_t strength, size_t speed,
                           size_t lifetime, const std::vector<std::string> properties,
                           std::string figurepath) :
    creaturename(creaturename), strength(strength), speed(speed), lifetime(lifetime),
    properties(properties), figurepath(figurepath)
{
    CreatureData::creatureCount++;
}


void CreatureData::printCreatureDataToConsole() const{
    std::cout << this->creaturename << "\n";
    std::cout << this->strength << "\n";
    std::cout << this->speed << "\n";
    std::cout << this->lifetime << "\n";
    for (int i = 0; i < this->properties.size(); i++) {
        std::cout << this->properties[i] << "\n";
    }
    std::cout << this->figurepath << "\n";
    return;
}
