/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    read file, read row, split row, check row, create creature
    storing statistical and error information in data-objects
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "textFileReader.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <regex>

#include "exceptions.hpp"
#include "creature.hpp"


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ helper methods, declaration /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
namespace helperTextFileReader {
void splitString(std::string str,
                 std::string delimiter,
                 std::vector<std::string> &vector);
void addErrorLine(std::string errorMessage,
                  StatisticalFileReadingData &statisticalFileReadingData,
                  ErrorFileReadingData &errorFileReadingData);
}

// helper method only needed by readCreatureFile to sort the returned list
bool creatureListComparator(const Creature &cd1, const Creature &cd2) {
    return cd1.creaturename[0] < cd2.creaturename[0];
}

std::list<Creature> textFileReader::readCreatureFile(const std::string &filePath) {

    StatisticalFileReadingData statisticalFileReadingData;
    ErrorFileReadingData errorFileReadingData;
    std::list<Creature> creatureList;
    std::fstream infile(filePath, std::fstream::in);
    // information from one row
    std::vector<std::string> creatureInfo;
    std::string rowDescription;
    if(!infile) throw badTextFilePath();
    while (infile.good()) {
        std::getline(infile, rowDescription);
        statisticalFileReadingData.rownumber++;
        // text file line not empty
        if (rowDescription.empty()) {
            errorFileReadingData.errorInfo.push_back(
                        std::string("Empty line found. Line: ").append(
                            std::to_string(statisticalFileReadingData.rownumber)));
            statisticalFileReadingData.rowsincorrect++;
            errorFileReadingData.errorInfoCount++;
            continue;
        }
        // splitting & storing temporarily in creatureInfo
        textFileReader::splitCreatureRow(rowDescription, creatureInfo);
        if (correctRow(creatureInfo, statisticalFileReadingData, errorFileReadingData)) {
            creatureList.push_back(createCreatureFromRow(creatureInfo));
            statisticalFileReadingData.rowscorrect++;
        }
        else {
            creatureInfo.clear();
            statisticalFileReadingData.rowsincorrect++;
        }
    }
    std::cout << "\n";
    std::cout << "Read rows: " << statisticalFileReadingData.rownumber << std::endl;
    std::cout << "Correct rows: " << statisticalFileReadingData.rowscorrect << std::endl;
    std::cout << "Incorrect rows: " << statisticalFileReadingData.rowsincorrect << std::endl;
    std::cout << "" << std::endl;
    for (int i = 0; i < errorFileReadingData.errorInfo.size(); i++) {
        std::cout << errorFileReadingData.errorInfo[i] << std::endl;
    }
    creatureList.sort(creatureListComparator);
    return creatureList;
}


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ splitCreatureRow /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
void textFileReader::splitCreatureRow(const std::string &rowDescription,
                                      std::vector<std::string> &tempCreatureInfo) {
    helperTextFileReader::splitString(rowDescription, ",", tempCreatureInfo);
    std::cout << "\n";
    return;
}


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ correctRow /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
bool textFileReader::correctRow(const std::vector<std::string> &creatureInfo,
                                StatisticalFileReadingData &statisticalFileReadingData,
                                ErrorFileReadingData &errorFileReadingData) {
    bool valid = true;
    // TODO Discuss: bool flag valid is needed, because all mistakes in each line are to be found at the first try loading the file
    // valid number of collums per line for creating a creature
    if (creatureInfo.size() == 6) {
        // äüößÄÜÖ
        std::regex creatureNameRegex("[a-zA-Z\\s]+");
        // valid creaturename
        if (!std::regex_match(creatureInfo[0], creatureNameRegex)) {
            helperTextFileReader::addErrorLine("Invalid creature name. Line:",
                                               statisticalFileReadingData, errorFileReadingData);
            valid = false;
        }
        std::regex creatureStrengthRegex("[0-9]+");
        // valid strengh
        if (!std::regex_match(creatureInfo[1], creatureStrengthRegex)|| std::stoi(creatureInfo[1]) < 0 ) {
            helperTextFileReader::addErrorLine("Only positive integer strength is allowed. Line: ",
                                               statisticalFileReadingData, errorFileReadingData);
            valid = false;
        }
        std::regex creatureSpeedRegex("[0-9]+");
        // valid speed
        if (!std::regex_match(creatureInfo[2], creatureSpeedRegex) || std::stoi(creatureInfo[2]) < 0) {
            helperTextFileReader::addErrorLine("Only positive integer speed is allowed. Line: ",
                                               statisticalFileReadingData, errorFileReadingData);
            valid = false;
        }
        std::regex creatureLifetimeRegex("[0-9]+");
        // valid lifetime
        if (!std::regex_match(creatureInfo[3], creatureLifetimeRegex) || std::stoi(creatureInfo[3]) < 0) {
            helperTextFileReader::addErrorLine("Only positive integer lifetime is allowed. Line: ",
                                               statisticalFileReadingData, errorFileReadingData);
            valid = false;
        }
        std::regex creaturePropertiesRegex("[a-zA-Z0-9_\\s]+");
        // valid properties
        if (!std::regex_match(creatureInfo[4], creaturePropertiesRegex)) {
            helperTextFileReader::addErrorLine("Invalid creature properties. Line: ",
                                               statisticalFileReadingData, errorFileReadingData);
            valid = false;
        }
        std::regex creatureFilePathRegexLand("land/[a-zA-Z0-9]+.tga");
        std::regex creatureFilePathRegexWasser("wasser/[a-zA-Z0-9]+.tga");
        // valid path
        if (!std::regex_match(creatureInfo[5], creatureFilePathRegexLand) &&
                !std::regex_match(creatureInfo[5], creatureFilePathRegexWasser)) {
            helperTextFileReader::addErrorLine("Invalid creature file path. Line: ",
                                               statisticalFileReadingData, errorFileReadingData);
            valid = false;
        }
    } else {
        helperTextFileReader::addErrorLine("Incorrect number of collumns. Line: ",
                                           statisticalFileReadingData, errorFileReadingData);
        valid = false;
    }
    return valid;
}


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ createCreatureFromRow /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
Creature textFileReader::createCreatureFromRow(std::vector<std::string> &creatureInfo) {

    std::vector<std::string> tempProperties;
    helperTextFileReader::splitString(creatureInfo[4], " ", tempProperties);

    //deletes "" from tempProperties which equals creatureInfo[4]
    int deleteCount = 0;
    for (int i = 0; i - deleteCount < tempProperties.size(); i++) {
        if (tempProperties[i - deleteCount] == "") {
            tempProperties.erase(tempProperties.begin() + (i - deleteCount));
            deleteCount++;
        }
    }

    std::string tempCreatureName = creatureInfo[0];
    size_t tempStrength = atoi(creatureInfo[1].c_str());
    size_t tempSpeed = atoi(creatureInfo[2].c_str());
    size_t tempLifetime = atoi(creatureInfo[3].c_str());
    std::string tempImageFilePath = creatureInfo[5];

    CreatureTileType tempCreatureTileType;
    std::regex creatureFilePathRegexLand("land/[a-zA-Z0-9]+.tga");
    std::regex creatureFilePathRegexWasser("wasser/[a-zA-Z0-9]+.tga");

    if (std::regex_match(tempImageFilePath, creatureFilePathRegexLand)) {
        tempCreatureTileType = TERESTIAL;
    } else if (std::regex_match(tempImageFilePath, creatureFilePathRegexWasser)) {
        tempCreatureTileType = WATER;
    } else {
        throw badCreatureType();
    }
    Creature creature(tempCreatureName,
                      tempStrength,
                      tempSpeed,
                      tempLifetime,
                      tempProperties,
                      tempImageFilePath,
                      tempCreatureTileType);

    creatureInfo.clear();
    //creature.printCreatureDataToConsole();              // control output
    return creature;
}


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ helper methods, initialisation /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
void helperTextFileReader::splitString(std::string str,
                                       std::string delimiter,
                                       std::vector<std::string>& vector) {
    size_t substrStart = 0;
    size_t substrEnd = 0;
    while (substrStart < str.length()) {
        if (substrEnd > 10000) { break; }               // TODO Note: avoid this hack [10000] --> actually is ok
        substrEnd = str.find(delimiter, substrStart);
        std::string vectorElement = str.substr(substrStart, substrEnd - substrStart);
        vector.push_back(vectorElement);
        substrStart = substrEnd + 1;
    }
    return;
}

void helperTextFileReader::addErrorLine(std::string errorMessage,
                                        StatisticalFileReadingData &statisticalFileReadingData,
                                        ErrorFileReadingData &errorFileReadingData) {
    errorFileReadingData.errorInfo.push_back(
                std::string(errorMessage).append(
                    std::to_string(statisticalFileReadingData.rownumber)));
    errorFileReadingData.errorInfoCount++;
}
