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
        // TODO Test: showing error window if wrong textfile path is given.
        creatureDataFilepath = creatureDataFilepath.append("CreatureTable_mitFehlern.txt");
    } else {
        creatureDataFilepath = creatureDataFilepath.append("CreatureTable.txt");
    }
    std::cout << "\n";
    loadCreatures(creatureDataFilepath);
    loadImages(relativePath); // relativePath is imageDataFilepath
}

void GameModel::loadImages(const std::string &imageDataFilepath) {
    std::string relativePathLand = imageDataFilepath + "land/";
    std::string relativePathTerrain = imageDataFilepath + "terrain/";
    std::string relativePathWasser = imageDataFilepath + "wasser/";

    //this->sand.reset(new std::vector<unsigned char>(ImageTga::createImageVector(relativePathTerrain + "sand.tga")));
    this->sand = ImageTga::createImageVector(relativePathTerrain + "sand.tga");
    this->deep_sea = ImageTga::createImageVector(relativePathTerrain + "deep_sea.tga");
    this->birne = ImageTga::createImageVector(relativePathLand + "birne.tga");
    this->delphin = ImageTga::createImageVector(relativePathWasser + "delphin.tga");

    //landscape
    //this->landscape = LandscapeGrid::createLandscapeGrid(); // creates default landscapegrid for testing purpose
}

/*// helper method: only needed by loadCreatures // not needed any more
bool creatureListComparator(const CreatureData &cd1, const CreatureData &cd2) {
    return cd1.creaturename[0] < cd2.creaturename[0];
}*/

void GameModel::loadCreatures(const std::string &creatureDataFilepath) {
    this->creatureDataList = QList<CreatureData>::fromStdList(textFileReader::readCreatureFile(creatureDataFilepath));
    //this->textFileReaderObj.reset(new textFileReader(textFileReader(creatureDataFilepath)));
    //std::list<CreatureData> tempList = textFileReader::readCreatureFile(creatureDataFilepath, sfrd, efrd);
    //tempList.sort(creatureListComparator);
    //QList<CreatureData> qtempList = QList<CreatureData>::fromStdList(tempList);
    //creatureList = qtempList;
}


void GameModel::loadLandscapeGrid(GameModel &gamemodel) {
    // futher capsuling done here because advanced logic is needed (perl noise)
    //this->landscapeGrid.reset(new ...static Method of landscapegrid class);
    //landscapeGrid.reset(new LandscapeGrid(LandscapeGrid::createLandscapeGrid(gamemodel)));
}


