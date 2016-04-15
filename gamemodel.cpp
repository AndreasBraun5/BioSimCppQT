/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    gamemodel: constains gamelogic and gamedata
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "gamemodel.hpp"

#include <iostream>

#include "imagetga.hpp"
#include "textfilereader.hpp"
#include "landscape.hpp" //TODO


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class GameModel /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
GameModel::GameModel(const std::string &relativePath) {
    setUpGamemodel(relativePath);
}

void GameModel::setUpGamemodel(const std::string &relativePath) {
    // TODO AB0: interaction with the user is normally done by biosim.cpp
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

    //TODO Test: image debug output
    //this->sand.reset(new ImageTga(ImageTga::createCorrectQImage(relativePathTerrain + "sand.tga")));

    // TODO AB2: all images need to be loaded. All terrain images are already.
    // TODO Test: showing error window if wrong image path is given at start.
    // land
    this->birne.reset(new ImageTga(ImageTga::createCorrectImageTga(relativePathLand + "birne.tga")));
    this->busch.reset(new ImageTga(ImageTga::createCorrectImageTga(relativePathLand + "busch.tga")));

    //terrain
    this->deep_seaImageTga.reset(new ImageTga(ImageTga::createCorrectImageTga(relativePathTerrain + "deep_sea.tga")));
    this->earthImageTga.reset(new ImageTga(ImageTga::createCorrectImageTga(relativePathTerrain + "earth.tga")));
    this->rocksImageTga.reset(new ImageTga(ImageTga::createCorrectImageTga(relativePathTerrain + "rocks.tga")));
    //TODO AB0: if sand_kopie.tga use, where in midst something is deletet, then same display error. Problem exists with
    // pixel values 0,0,0 and 255,255,255
    this->sandImageTga.reset(new ImageTga(ImageTga::createCorrectImageTga(relativePathTerrain + "sand.tga")));
    this->shallow_waterImageTga.reset(new ImageTga(ImageTga::createCorrectImageTga(relativePathTerrain + "shallow_water.tga")));
    this->snowImageTga.reset(new ImageTga(ImageTga::createCorrectImageTga(relativePathTerrain + "snow.tga")));

    this->deep_seaPixmap.reset(new QPixmap(QPixmap::fromImage(deep_seaImageTga.data()->qImage)));
    this->earthPixmap.reset(new QPixmap(QPixmap::fromImage(earthImageTga.data()->qImage)));
    this->rocksPixmap.reset(new QPixmap(QPixmap::fromImage(rocksImageTga.data()->qImage)));
    this->sandPixmap.reset(new QPixmap(QPixmap::fromImage(sandImageTga.data()->qImage)));
    this->shallow_waterPixmap.reset(new QPixmap(QPixmap::fromImage(shallow_waterImageTga.data()->qImage)));
    this->snowPixmap.reset(new QPixmap(QPixmap::fromImage(snowImageTga.data()->qImage)));

    this->sandBlankPixmap = QPixmap::fromImage(sandImageTga.data()->qImage);

    // wasser
    this->algen.reset(new ImageTga(ImageTga::createCorrectImageTga(relativePathWasser + "algen.tga")));
    this->delpin.reset(new ImageTga(ImageTga::createCorrectImageTga(relativePathWasser + "delphin.tga")));

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
    for(int i = 0; i <= 1; i++){
        for(int j = 0; j <= 10; j++){
            std::cout << tempQImage.pixelColor(i,j).alpha() << " alpha " <<
                         tempQImage.pixelColor(i,j).red() << " red " <<
                         tempQImage.pixelColor(i,j).green() << " green " <<
                         tempQImage.pixelColor(i,j).blue() << " blue \n";
        }
    }
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

//TODO
void GameModel::loadLandscapeGrid(GameModel &gamemodel) { //TODO AB4: additional parameters at compiletime
    // futher capsuling done here because advanced logic is needed (perl noise)
    //this->landscapeGrid.reset(new ...static Method of landscapegrid class); //TODO AB4: additional parameters at compiletime
    landscapeGrid.reset(new LandscapeGrid(LandscapeGrid::createLandscapeGrid(gamemodel)));
}


