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
    std::string creatureDataFilepath = relativePath;
    creatureDataFilepath = creatureDataFilepath.append("CreatureTable.txt");
    std::cout << "Using CreatureTable.txt \n";
    /*/
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
    /*/
    loadCreatures(creatureDataFilepath);
    loadImages(relativePath); // relativePath is imageDataFilepath
    loadLandscapeGrid(500, 500); // parameter at compiletime are given here
    // TODO map size
}

void GameModel::loadImages(const std::string &imageDataFilepath) {

    std::string relativePathTerrain = imageDataFilepath + "terrain/";

    // general images
    this->imageMap["cursor"] = ImageTga::createImageVector(imageDataFilepath + "/cursor.tga");
    this->imageMap["dead"] = ImageTga::createImageVector(imageDataFilepath + "/dead.tga");
    this->imageMap["path"] = ImageTga::createImageVector(imageDataFilepath + "/path.tga");

    // landscape images
    this->imageMap["deep_sea"] = ImageTga::createImageVector(relativePathTerrain + "/deep_sea.tga");
    this->imageMap["shallow_water"] = ImageTga::createImageVector(relativePathTerrain + "/shallow_water.tga");
    this->imageMap["sand"] = ImageTga::createImageVector(relativePathTerrain + "/sand.tga");
    this->imageMap["earth"] = ImageTga::createImageVector(relativePathTerrain + "/earth.tga");
    this->imageMap["rocks"] = ImageTga::createImageVector(relativePathTerrain + "/rocks.tga");
    this->imageMap["snow"] = ImageTga::createImageVector(relativePathTerrain + "/snow.tga");

    // creature images
    for (int i=0; i<creaturesPossibleList.size(); i++) {
        this->imageMap[creaturesPossibleList.at(i).creaturename] =
                ImageTga::createImageVector(imageDataFilepath + creaturesPossibleList.at(i).figurepath);
    }
}

void GameModel::loadCreatures(const std::string &creatureDataFilepath) {
    this->creaturesPossibleList = QList<Creature>::fromStdList(textFileReader::readCreatureFile(creatureDataFilepath));
}

void GameModel::loadLandscapeGrid(unsigned int sizehorizontal, unsigned int sizevertical) {
    this->landscapeGridmap = LandscapeGrid::createLandscapeGrid(sizehorizontal, sizevertical);
}


