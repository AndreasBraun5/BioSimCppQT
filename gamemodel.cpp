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
    loadLandscapeGrid(500, 500); // parameter at compiletime are given here
    // test adding one predefined creature from the list of choices to the gridlist
    // TODO: position
    this->creaturesAllOnGrid.append(this->creaturesPossibleList.at(1));
    this->creaturesAllOnGrid.append(this->creaturesPossibleList.at(2));
}

void GameModel::loadImages(const std::string &imageDataFilepath) {
    std::string relativePathLand = imageDataFilepath + "land/";
    std::string relativePathTerrain = imageDataFilepath + "terrain/";
    std::string relativePathWasser = imageDataFilepath + "wasser/";

    // images
    this->cursor = ImageTga::createImageVector(imageDataFilepath + "/cursor.tga");
    this->dead = ImageTga::createImageVector(imageDataFilepath + "/dead.tga");
    this->path = ImageTga::createImageVector(imageDataFilepath + "/path.tga");
    // terrain
    this->deep_sea = ImageTga::createImageVector(relativePathTerrain + "deep_sea.tga");
    this->shallow_water = ImageTga::createImageVector(relativePathTerrain + "shallow_water.tga");
    this->sand = ImageTga::createImageVector(relativePathTerrain + "sand.tga");
    this->earth = ImageTga::createImageVector(relativePathTerrain + "earth.tga");
    this->rocks = ImageTga::createImageVector(relativePathTerrain + "rocks.tga");
    this->snow = ImageTga::createImageVector(relativePathTerrain + "snow.tga");
    // land
    this->birne = ImageTga::createImageVector(relativePathLand + "birne.tga");
    this->busch = ImageTga::createImageVector(relativePathLand + "busch.tga");
    this->eiche = ImageTga::createImageVector(relativePathLand + "eiche.tga");
    this->emu = ImageTga::createImageVector(relativePathLand + "emu.tga");
    this->gras = ImageTga::createImageVector(relativePathLand + "gras.tga");
    this->hund = ImageTga::createImageVector(relativePathLand + "hund.tga");
    this->kaktus = ImageTga::createImageVector(relativePathLand + "kaktus.tga");
    this->kuh = ImageTga::createImageVector(relativePathLand + "kuh.tga");
    this->pferd = ImageTga::createImageVector(relativePathLand + "pferd.tga");
    this->schaf = ImageTga::createImageVector(relativePathLand + "schaf.tga");
    this->sonnenblume = ImageTga::createImageVector(relativePathLand + "sonnenblume.tga");
    this->tanne = ImageTga::createImageVector(relativePathLand + "tanne.tga");
    this->tiger = ImageTga::createImageVector(relativePathLand + "tiger.tga");
    this->ursus = ImageTga::createImageVector(relativePathLand + "ursus.tga");
    // wasser
    this->algen = ImageTga::createImageVector(relativePathWasser + "algen.tga");
    this->delphin = ImageTga::createImageVector(relativePathWasser + "delphin.tga");
    this->forelle = ImageTga::createImageVector(relativePathWasser + "forelle.tga");
    this->hai = ImageTga::createImageVector(relativePathWasser + "hai.tga");
    this->krabbe = ImageTga::createImageVector(relativePathWasser + "krabbe.tga");
    this->plankton = ImageTga::createImageVector(relativePathWasser + "plankton.tga");
    this->seetang = ImageTga::createImageVector(relativePathWasser + "seetang.tga");
    this->wels = ImageTga::createImageVector(relativePathWasser + "wels.tga");
}

void GameModel::loadCreatures(const std::string &creatureDataFilepath) {
    this->creaturesPossibleList = QList<Creature>::fromStdList(textFileReader::readCreatureFile(creatureDataFilepath));
}

void GameModel::loadLandscapeGrid(unsigned int sizehorizontal, unsigned int sizevertical) {
    this->landscapeGridmap = LandscapeGrid::createLandscapeGrid(sizehorizontal, sizevertical);
}


