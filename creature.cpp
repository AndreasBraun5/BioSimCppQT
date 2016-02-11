/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    creature data, creature logic
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/



/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ #include /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "Creature.h"
#include <fstream>
#include <vector>
#include <string>

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ static variable initialising /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
int CreatureData::creatureCount = 0;


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ constructors /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
CreatureData::CreatureData() {
    CreatureData::creatureCount++;
    this->creatureID = creatureCount;
}

CreatureData::CreatureData(std::string creaturename, size_t strength, size_t speed,
                           size_t lifetime, const std::vector<std::string> properties, std::string figurepath) {
    CreatureData::creatureCount++;
    this->creatureID = creatureCount;
    this->creaturename = creaturename;
    this->strength = strength;
    this->speed = speed;
    this->lifetime = lifetime;
    this->properties = properties;
    this->figurepath = figurepath;
}


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ printCreatureDataToConsole /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
void CreatureData::printCreatureDataToConsole(){
    PRINT(this->creatureID)
            PRINT(this->creaturename);
    PRINT(this->strength);
    PRINT(this->speed);
    PRINT(this->lifetime);
    for (int i = 0; i < this->properties.size(); i++) {
        PRINT(this->properties[i]);
    }
    PRINT(this->figurepath);
    return;
}
