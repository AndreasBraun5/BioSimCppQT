/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    gamemodel
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
        creatureDataFilepath = creatureDataFilepath.append("CreatureTable_mitFehlern.txt");
    } else {
        creatureDataFilepath = creatureDataFilepath.append("CreatureTable.txt");
    }
    std::cout << "\n";

    try {
        loadCreatures(creatureDataFilepath);
    } catch (std::exception &e) {
        std::cout << e.what() << "/n" << creatureDataFilepath;
    }

    // TODO Unfinished: try catch
    loadImages(relativePath);
}

void GameModel::loadImages(const std::string &relativePath) {
    std::string relativePathLand = relativePath + "land/";
    std::string relativePathTerrain = relativePath + "terrain/";
    std::string relativePathWasser = relativePath + "wasser/";

    // TODO Unfinished: all images need to be loaded
    try {
        // test
        this->sand.reset(&ImageTga::createCorrectQImage(relativePath + "terrain/sand.tga"));

        // land
        this->birne.reset(&ImageTga::createCorrectQImage(relativePathLand + "birne.tga"));
        this->busch.reset(&ImageTga::createCorrectQImage(relativePathLand + "busch.tga"));

        //terrain
        this->deep_sea.reset(&ImageTga::createCorrectQImage(relativePathTerrain + "deep_sea.tga"));
        this->earth.reset(&ImageTga::createCorrectQImage(relativePathTerrain + "earth.tga"));

        // wasser
        this->algen.reset(&ImageTga::createCorrectQImage(relativePathWasser + "algen.tga"));
        this->delpin.reset(&ImageTga::createCorrectQImage(relativePathWasser + "delphin.tga"));
    } catch(std::exception &e) {
        std::cout << e.what();
    }
}

// helper method: only needed by loadCreatures
bool creatureListComparator(const CreatureData &cd1, const CreatureData &cd2) {
    return cd1.creaturename[0] < cd2.creaturename[0];
}

void GameModel::loadCreatures(const std::string &creatureDataFilepath) {
    StatisticalFileReadingData sfrd;
    ErrorFileReadingData efrd;
    QList<CreatureData> tempList = QList<CreatureData>::fromStdList(textFileReader::readCreatureFile(creatureDataFilepath, sfrd, efrd));
    qSort(tempList.begin(), tempList.end(),creatureListComparator);
    creatureList = tempList;
}


