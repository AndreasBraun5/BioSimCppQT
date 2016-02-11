/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    read file, read row, split row, check row, create creature
    storing statistical and error information in data-objects
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/

// TODO const
// TODO Exceptions

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ #include /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "TextFileReader.h"
#include<fstream>
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <regex>
//#include <exception>

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ helper methods /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
void splitString(std::string str, std::string delimiter, std::vector<std::string>& vector);
void addErrorLine(std::string);


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ static variable initialising /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
int StatisticalFileReadingData::rownumber = 0;
int StatisticalFileReadingData::rowscorrect = 0;
int StatisticalFileReadingData::rowsincorrect = 0;
int ErrorFileReadingData::errorInfoCount = 0;
std::vector<std::string> ErrorFileReadingData::errorInfo(100);                      // TODO Avoid Hack [100], dynamische Initialisierung möglich auch bei static?


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ constructors /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
// only standard construtor is implemented


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ readCreatureFile /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
std::list<CreatureData> TextFileReader::readCreatureFile(const std::string filepath) {
    std::list<CreatureData> creatureList;
    std::fstream infile(filepath, std::fstream::in);
    if (!infile.good()) {
        PRINT(&std::ios::rdstate);
        PRINT(&std::ios::badbit);
        PRINT(&std::ios::eofbit);
        PRINT(&std::ios::failbit);
        std::cerr << filepath << " Creature file cannot be opened!\n";
    }
    else {
        std::vector<std::string> creatureInfo;										// information from one row
        std::string rowDescription;
        while (infile.good()) {
            std::getline(infile, rowDescription);
            StatisticalFileReadingData::rownumber++;
            if (!rowDescription.empty()) {											// Zeile nicht leer
                TextFileReader::splitCreatureRow(rowDescription, creatureInfo);		// splitting & storing temporarily in creatureInfo
                if (correctRow(creatureInfo)) {										// checking row	TODO Fehler bricht ab nach den Algen...
                    creatureList.push_back(createCreatureFromRow(creatureInfo));	// adding a creature to the list
                    StatisticalFileReadingData::rowscorrect++;
                }
                else {
                    creatureInfo.clear();
                    StatisticalFileReadingData::rowsincorrect++;
                }
            } else {
                ErrorFileReadingData::errorInfo[ErrorFileReadingData::errorInfoCount] =
                        std::string("Empty line found. Line: ").append(std::to_string(StatisticalFileReadingData::rownumber));
                ErrorFileReadingData::errorInfoCount++;
            }
        }

        PRINT("");
        std::cout << "Read rows: " << StatisticalFileReadingData::rownumber << std::endl;
        std::cout << "Correct rows: " << StatisticalFileReadingData::rowscorrect << std::endl;
        std::cout << "Incorrect rows: " << StatisticalFileReadingData::rowsincorrect << std::endl;
        std::cout << "" << std::endl;
        for (int i = 0; i < ErrorFileReadingData::errorInfo.size(); i++) {
            std::cout << ErrorFileReadingData::errorInfo[i] << std::endl;
        }
    }
    return creatureList;
}


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ splitCreatureRow /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
void TextFileReader::splitCreatureRow(const std::string rowDescription, std::vector<std::string>& tempCreatureInfo) {
    splitString(rowDescription,",", tempCreatureInfo);
    PRINT("");
    return;
}


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ correctRow /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
bool TextFileReader::correctRow(const std::vector<std::string>& creatureInfo) {
    bool valid = true;
    if (creatureInfo.size() == 6) {
        // äüößÄÜÖ
        std::regex creatureNameRegex("[a-zA-Z\\s]+");                                   // valid creaturename
        if (!std::regex_match(creatureInfo[0], creatureNameRegex)) {
            valid = false;
            addErrorLine("Invalid creature name. Line:");
        }
        std::regex creatureStrengthRegex("[0-9]+");                                     // valid strengh
        if (!std::regex_match(creatureInfo[1], creatureStrengthRegex)|| std::stoi(creatureInfo[1]) < 0 ) {
            valid = false;
            addErrorLine("Only positive integer strength is allowed. Line: ");
        }

        std::regex creatureSpeedRegex("[0-9]+");                                        // valid speed
        if (!std::regex_match(creatureInfo[2], creatureSpeedRegex) || std::stoi(creatureInfo[2]) < 0) {
            valid = false;
            addErrorLine("Only positive integer speed is allowed. Line: ");
        }

        std::regex creatureLifetimeRegex("[0-9]+");                                     // valid lifetime
        if (!std::regex_match(creatureInfo[3], creatureLifetimeRegex) || std::stoi(creatureInfo[3]) < 0) {
            valid = false;
            addErrorLine("Only positive integer lifetime is allowed. Line: ");
        }

        std::regex creaturePropertiesRegex("[a-zA-Z0-9_\\s]*");                         // valid properties HACK
        if (!std::regex_match(creatureInfo[4], creaturePropertiesRegex)) {
            valid = false;
            addErrorLine("Invalid creature properties. Line: ");
        }

        std::regex creatureFilePathRegex("[a-zA-Z0-9]+/[a-zA-Z0-9]+.[a-zA-Z0-9]+");     // valid path HACK
        if (!std::regex_match(creatureInfo[5], creatureFilePathRegex)) {
            valid = false;
            addErrorLine("Invalid creature file path. Line: ");
        }
    } else {
        valid = false;
        addErrorLine("Incorrect number of collumns. Line: ");
    }

    return valid;
}


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ createCreatureFromRow /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
CreatureData TextFileReader::createCreatureFromRow(std::vector<std::string>& creatureInfo) {

    std::vector<std::string> tempProperties;
    splitString(creatureInfo[4], " ", tempProperties);

    //deletes "" from tempProperties which equals creatureInfo[4]
    int deleteCount = 0;
    for (int i = 0; i - deleteCount < tempProperties.size(); i++) {
        if (tempProperties[i - deleteCount] == "") {
            tempProperties.erase(tempProperties.begin() + (i - deleteCount));
            deleteCount++;
        }
    }

    size_t tempStrength = atoi(creatureInfo[1].c_str());
    size_t tempSpeed = atoi(creatureInfo[2].c_str());
    size_t tempLifetime = atoi(creatureInfo[3].c_str());
    CreatureData creature{creatureInfo[0],
                tempStrength,
                tempSpeed,
                tempLifetime,
                tempProperties,
                creatureInfo[5]
                         };

    creatureInfo.clear();
    creature.printCreatureDataToConsole();              // control output
    return creature;
}


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ helper methods, declaration /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
void splitString(std::string str, std::string delimiter, std::vector<std::string>& vector) {
    size_t substrStart = 0;
    size_t substrEnd = 0;
    while (substrStart < str.length()) {
        if (substrEnd > 10000) { break; }               // TODO Question: how to avoid this hack? [10000]
        substrEnd = str.find(delimiter, substrStart);
        std::string vectorElement = str.substr(substrStart, substrEnd - substrStart);
        vector.push_back(vectorElement);
        substrStart = substrEnd + 1;
    }
    return;
}

void addErrorLine(std::string errorMessage){
    ErrorFileReadingData::errorInfo[ErrorFileReadingData::errorInfoCount] =
            std::string(errorMessage).append(std::to_string(StatisticalFileReadingData::rownumber));
    ErrorFileReadingData::errorInfoCount++;
}
