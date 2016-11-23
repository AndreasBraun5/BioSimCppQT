/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    All stuff regarding creatures encapsuled.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "creature.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class CreatureData /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
// default position value is zero.
Creature::Creature(const std::string &creaturename,
                   size_t strength,
                   size_t speed,
                   size_t lifetime,
                   const std::vector<std::string> &properties,
                   const std::string &figurepath,
                   CreatureTileType creatureTileType
                   )
    : creaturename(creaturename), strength(strength), speed(speed), lifetime(lifetime),
      properties(properties), figurepath(figurepath),
      // default setting of position and creatureTileType
      positionX(0), positionY(0), creatureTileType(creatureTileType) {
    // due to default type being Terestial it only needs to be changed to water type
}


void Creature::printCreatureDataToConsole() const {
    std::cout << this->creaturename << "\n";
    std::cout << this->strength << "\n";
    std::cout << this->speed << "\n";
    std::cout << this->lifetime << "\n";
    for (int i = 0; i < this->properties.size(); i++) {
        std::cout << this->properties[i] << "\n";
    }
    std::cout << this->figurepath << "\n";
    std::cout << this->positionX << "\n";
    std::cout << this->positionY << "\n";
    return;
}
