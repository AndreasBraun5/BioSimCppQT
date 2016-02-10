/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*/
    read file, read row, split row, check row, create creature
    storing statistical and error information in data-objects
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

// TODO const
// TODO Exceptions

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "TextFileReader.h"

#include<fstream>
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <regex>
//#include <exception>


void splitString(std::string str, std::string delimiter, std::vector<std::string>& vector);

int StatisticalFileReadingData::rownumber = 0;
int StatisticalFileReadingData::rowscorrect = 0;
int StatisticalFileReadingData::rowsincorrect = 0;
int ErrorFileReadingData::errorInfoCount = 0;

std::vector<std::string> ErrorFileReadingData::errorInfo(100);						// TODO Avoid Hack [100], dynamische Initialisierung möglich auch bei static?

// Finished
void TextFileReader::readCreatureFile(std::string filepath, std::list<CreatureData>& creatureList) {
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
    return;
}

//  FINISHED
void TextFileReader::splitCreatureRow(std::string rowDescription, std::vector<std::string>& creatureInfo) {
    splitString(rowDescription,",", creatureInfo);
    PRINT("");
    return;
}

// Finished
bool TextFileReader::correctRow(std::vector<std::string>& creatureInfo) {
    bool valid = true;
    if (creatureInfo.size() == 6) {
        // äüößÄÜÖ
        std::regex creatureNameRegex("[a-zA-Z\\s]+");                                   // valid creaturename
        if (!std::regex_match(creatureInfo[0], creatureNameRegex)) {
            valid = false;
            ErrorFileReadingData::errorInfo[ErrorFileReadingData::errorInfoCount] =
                std::string("Invalid creature name. Line:").append(std::to_string(StatisticalFileReadingData::rownumber));
            ErrorFileReadingData::errorInfoCount++;
        }                                                                               // valid strengh
        std::regex creatureStrengthRegex("[0-9]+");
        if (!std::regex_match(creatureInfo[1], creatureStrengthRegex)) {
            valid = false;
            ErrorFileReadingData::errorInfo[ErrorFileReadingData::errorInfoCount] =
                std::string("Only positive integer strength is allowed. Line: ").append(std::to_string(StatisticalFileReadingData::rownumber));
            ErrorFileReadingData::errorInfoCount++;
        }
        else if (std::stoi(creatureInfo[1]) < 0) {
            valid = false;
            ErrorFileReadingData::errorInfo[ErrorFileReadingData::errorInfoCount] =
                std::string("Only positive integer strength is allowed. Line: ").append(std::to_string(StatisticalFileReadingData::rownumber));
            ErrorFileReadingData::errorInfoCount++;
        }

        std::regex creatureSpeedRegex("[0-9]+");                                        // valid speed
        if (!std::regex_match(creatureInfo[2], creatureSpeedRegex)) {
            valid = false;
            ErrorFileReadingData::errorInfo[ErrorFileReadingData::errorInfoCount] =
                std::string("Only positive integer speed is allowed. Line: ").append(std::to_string(StatisticalFileReadingData::rownumber));
            ErrorFileReadingData::errorInfoCount++;
        }
        else if (std::stoi(creatureInfo[2]) < 0) {
            valid = false;
            ErrorFileReadingData::errorInfo[ErrorFileReadingData::errorInfoCount] =
                std::string("Only positive integer speed is allowed. Line: ").append(std::to_string(StatisticalFileReadingData::rownumber));
            ErrorFileReadingData::errorInfoCount++;
        }

        std::regex creatureLifetimeRegex("[0-9]+");                                     // valid lifetime
        if (!std::regex_match(creatureInfo[3], creatureLifetimeRegex)) {
            valid = false;
            ErrorFileReadingData::errorInfo[ErrorFileReadingData::errorInfoCount] =
                std::string("Only positive integer lifetime is allowed. Line: ").append(std::to_string(StatisticalFileReadingData::rownumber));
            ErrorFileReadingData::errorInfoCount++;
        }
        else if (std::stoi(creatureInfo[3]) < 0) {
            ErrorFileReadingData::errorInfo[ErrorFileReadingData::errorInfoCount] =
                std::string("Only positive integer lifetime is allowed. Line: ").append(std::to_string(StatisticalFileReadingData::rownumber));
            ErrorFileReadingData::errorInfoCount++;
        }

        std::regex creaturePropertiesRegex("[a-zA-Z0-9_\\s]*");                         // valid properties HACK
        if (!std::regex_match(creatureInfo[4], creaturePropertiesRegex)) {
            valid = false;
            ErrorFileReadingData::errorInfo[ErrorFileReadingData::errorInfoCount] =
                std::string("Invalid creature properties. Line: ").append(std::to_string(StatisticalFileReadingData::rownumber));
            ErrorFileReadingData::errorInfoCount++;
        }

        std::regex creatureFilePathRegex("[a-zA-Z0-9]+/[a-zA-Z0-9]+.[a-zA-Z0-9]+");     // valid path HACK
        if (!std::regex_match(creatureInfo[5], creatureFilePathRegex)) {
            valid = false;
            ErrorFileReadingData::errorInfo[ErrorFileReadingData::errorInfoCount] =
                std::string("Invalid creature file path. Line: ").append(std::to_string(StatisticalFileReadingData::rownumber));
            ErrorFileReadingData::errorInfoCount++;
        }
    } else {
        valid = false;
        ErrorFileReadingData::errorInfo[ErrorFileReadingData::errorInfoCount] =
            std::string("Incorrect number of collumns. Line: ").append(std::to_string(StatisticalFileReadingData::rownumber));
        ErrorFileReadingData::errorInfoCount++;
    }

    return valid;
}


//  FINISHED
CreatureData TextFileReader::createCreatureFromRow(std::vector<std::string>& creatureInfo) {
    CreatureData creature{};

    creature.creaturename = creatureInfo[0];
    creature.strength = atoi(creatureInfo[1].c_str());
    creature.speed = atoi(creatureInfo[2].c_str());
    creature.lifetime = atoi(creatureInfo[3].c_str());
    splitString(creatureInfo[4], " ", creature.properties);
    int deleteCount = 0;
    for (int i = 0; i - deleteCount < creature.properties.size(); i++) {
        if (creature.properties[i - deleteCount] == "") {
            creature.properties.erase(creature.properties.begin() + (i - deleteCount));
            deleteCount++;
        }
    }
    creature.figurepath = creatureInfo[5];


    creatureInfo.clear();
    PRINT(creature.creaturename);
    PRINT(creature.strength);
    PRINT(creature.speed);
    PRINT(creature.lifetime);
    for (int i = 0; i < creature.properties.size(); i++) {
        PRINT(creature.properties[i]);
    }
    PRINT(creature.figurepath);
    return creature;
}

// FINISHED
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
