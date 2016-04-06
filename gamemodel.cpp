/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    gamemodel: constains gamelogic and gamedata
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "gamemodel.hpp"

#include <iostream>

#include "imagetga.hpp"
#include "textfilereader.hpp"

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class GameModel /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
GameModel::GameModel(const std::string &relativePath) {
    setUpGamemodel(relativePath);
}
void GameModel::setUpGamemodel(const std::string &relativePath) {
    std::cout << "Enter number: \n 0 for CreatureTable_mitFehlern.txt \n 1 for CreatureTable.txt \n";
    int integer = 1;
    std::cin >> integer;
    std::string creatureDataFilepath = relativePath;
    if (integer == 0) {
        // TODO Test: "CreatureTableXXX.txt" Shows error if wrong textfile path is given.
        creatureDataFilepath = creatureDataFilepath.append("CreatureTable_mitFehlern.txt");
    } else {
        creatureDataFilepath = creatureDataFilepath.append("CreatureTable.txt");
    }
    std::cout << "\n";
    loadCreatures(creatureDataFilepath);
    loadImages(relativePath);
}

void GameModel::loadImages(const std::string &relativePath) {
    std::string relativePathLand = relativePath + "land/";
    std::string relativePathTerrain = relativePath + "terrain/";
    std::string relativePathWasser = relativePath + "wasser/";

    // TODO AB2: all images need to be loaded
    // TODO Test: "snd.tga" Shows error if wrong image path is given.
    // TODO reset Qscoped Pointer with new
    this->sand.reset(new ImageTga(ImageTga::createCorrectQImage(relativePath + "terrain/sand.tga")));
    //QImage test = this->sand->imageData;

    // land
    this->birne.reset(&ImageTga::createCorrectQImage(relativePathLand + "birne.tga"));
    this->busch.reset(&ImageTga::createCorrectQImage(relativePathLand + "busch.tga"));

    //terrain
    this->deep_sea.reset(new ImageTga(ImageTga::createCorrectQImage(relativePathTerrain + "deep_sea.tga")));
    this->earth.reset(&ImageTga::createCorrectQImage(relativePathTerrain + "earth.tga"));

    // wasser
    this->algen.reset(&ImageTga::createCorrectQImage(relativePathWasser + "algen.tga"));
    this->delpin.reset(&ImageTga::createCorrectQImage(relativePathWasser + "delphin.tga"));
}

// helper method: only needed by loadCreatures
bool creatureListComparator(const CreatureData &cd1, const CreatureData &cd2) {
    return cd1.creaturename[0] < cd2.creaturename[0];
}

void GameModel::loadCreatures(const std::string &creatureDataFilepath) {
    StatisticalFileReadingData sfrd;
    ErrorFileReadingData efrd;
    std::list<CreatureData> tempList = textFileReader::readCreatureFile(creatureDataFilepath, sfrd, efrd);
    tempList.sort(creatureListComparator);
    // TODO Note: qSort deprecated...
    QList<CreatureData> qtempList = QList<CreatureData>::fromStdList(tempList);
    creatureList = qtempList;
}


