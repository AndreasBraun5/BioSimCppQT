/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    gamemodel: constains gamelogic and gamedata
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "gamemodel.hpp"

#include <iostream>

#include "imagetga.hpp"
#include "textfilereader.hpp"
#include "landscape.hpp"


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class GameModel /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
GameModel::GameModel(const std::string &relativePath) {
    setUpGamemodel(relativePath);
}

void GameModel::setUpGamemodel(const std::string &relativePath) {
    // TODO Note: interaction with the user is normally done by biosim.cpp
    std::cout << "Enter number: \n 0 for CreatureTable_mitFehlern.txt \n 1 for CreatureTable.txt \n";
    int integer = 1;
    std::cin >> integer;
    std::string creatureDataFilepath = relativePath;
    if (integer == 0) {
        creatureDataFilepath = creatureDataFilepath.append("CreatureTable_mitFehlern.txt");
    } else {
        creatureDataFilepath = creatureDataFilepath.append("CreatureTable.txt");
    }
    std::cout << "\n";
    loadCreatures(creatureDataFilepath);
    loadImages(relativePath); // relativePath is imageDataFilepath
    loadLandscapeGrid(500, 500); // Parameter at compiletime are given here
}

void GameModel::loadImages(const std::string &imageDataFilepath) {
    std::string relativePathLand = imageDataFilepath + "land/";
    std::string relativePathTerrain = imageDataFilepath + "terrain/";
    std::string relativePathWasser = imageDataFilepath + "wasser/";

    this->deep_sea = ImageTga::createImageVector(relativePathTerrain + "deep_sea.tga");
    this->shallow_water = ImageTga::createImageVector(relativePathTerrain + "shallow_water.tga");
    this->sand = ImageTga::createImageVector(relativePathTerrain + "sand.tga");
    this->earth = ImageTga::createImageVector(relativePathTerrain + "earth.tga");
    this->rocks = ImageTga::createImageVector(relativePathTerrain + "rocks.tga");
    this->snow = ImageTga::createImageVector(relativePathTerrain + "snow.tga");

    this->birne = ImageTga::createImageVector(relativePathLand + "birne.tga");
    this->delphin = ImageTga::createImageVector(relativePathWasser + "delphin.tga");
}

void GameModel::loadCreatures(const std::string &creatureDataFilepath) {
    this->creatureDataList = QList<CreatureData>::fromStdList(textFileReader::readCreatureFile(creatureDataFilepath));
}

void GameModel::loadLandscapeGrid(unsigned int sizehorizontal, unsigned int sizevertical) {
    this->landscapeGridmap = LandscapeGrid::createLandscapeGrid(sizehorizontal, sizevertical);
}


