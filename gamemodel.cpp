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
        // TODO Test: showing error window if wrong textfile path is given.
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



    //this->sand.reset(new ImageTga(ImageTga::createCorrectQImage(relativePathTerrain + "sand.tga")));

    // TODO AB2: all images need to be loaded. All terrain images are already.
    // TODO Test: showing error window if wrong image path is given at start.
    // land
    this->birne.reset(new ImageTga(ImageTga::createCorrectQImage(relativePathLand + "birne.tga")));
    this->busch.reset(new ImageTga(ImageTga::createCorrectQImage(relativePathLand + "busch.tga")));

    //terrain
    this->deep_sea.reset(new ImageTga(ImageTga::createCorrectQImage(relativePathTerrain + "deep_sea.tga")));
    this->earth.reset(new ImageTga(ImageTga::createCorrectQImage(relativePathTerrain + "earth.tga")));
    this->rocks.reset(new ImageTga(ImageTga::createCorrectQImage(relativePathTerrain + "rocks.tga")));
    this->sand.reset(new ImageTga(ImageTga::createCorrectQImage(relativePathTerrain + "sand.tga")));
    this->shallow_water.reset(new ImageTga(ImageTga::createCorrectQImage(relativePathTerrain + "shallow_water.tga")));
    this->snow.reset(new ImageTga(ImageTga::createCorrectQImage(relativePathTerrain + "snow.tga")));

    // wasser
    this->algen.reset(new ImageTga(ImageTga::createCorrectQImage(relativePathWasser + "algen.tga")));
    this->delpin.reset(new ImageTga(ImageTga::createCorrectQImage(relativePathWasser + "delphin.tga")));

    // TODO Test: image debug output 3
    QImage tempQImage =  birne->qImage;
    std::cout << "\nTest: image debug output 3\n";
    std::cout << "Image heigth: " << tempQImage.height() << "\n";
    std::cout << "Image width: " << tempQImage.width() << "\n";
    std::cout << "Image byteCount: " << tempQImage.byteCount() << "\n";
    std::cout << "Image bytesPerLine: " << tempQImage.bytesPerLine() << "\n";
    std::cout << "Image data size QimageSizeHeight*QimageSizeWidth: " <<
                 tempQImage.size().height() * tempQImage.size().width() << "\n";
    std::cout << "bits per pixel: " << tempQImage.depth() << "\n";
    std::cout << "ImageFormat: " << tempQImage.format() << ", if 5 it is 32-bit ARGB \n";
    std::cout << "Image data pointer adress: " << tempQImage.data_ptr() <<"\n";
    std::cout << "first pixel down left:\n";
    std::cout << tempQImage.pixelColor(0,0).alpha() << " alpha\n" <<
                 tempQImage.pixelColor(0,0).red() << " red\n" <<
                 tempQImage.pixelColor(0,0).green() << " green\n" <<
                 tempQImage.pixelColor(0,0).blue() << " blue\n";
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


