/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/

/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "imagetga.h"
#include "creature.h"
#include <QMainWindow>
//#include "biosim.h" // circular dependency

class GameModel {
public: QList<CreatureData> creatureList;

    // TODO kinda weird class up till now. Initially meant to reserve memory here and
    // initialise with constructor, but because of deleted standard constructor not possible.


    std::string relativePath = "C:/GitHub/BioSimCppQT/GraficsTextfiles";

    // images for land
    std::string relativePathLand = relativePath.append("land/");
    // TODO doesn´t throw exceptions if biirne.tga
    ImageTga birne = ImageTga::createCorrectImage(relativePathLand.append("birne.tga"));
    ImageTga busch = ImageTga::createCorrectImage(relativePathLand.append("busch.tga"));
    ImageTga eiche = ImageTga::createCorrectImage(relativePathLand.append("eiche.tga"));
    ImageTga emu = ImageTga::createCorrectImage(relativePathLand.append("emu.tga"));
    ImageTga gras = ImageTga::createCorrectImage(relativePathLand.append("gras.tga"));
    ImageTga hund = ImageTga::createCorrectImage(relativePathLand.append("hund.tga"));
    ImageTga kaktus = ImageTga::createCorrectImage(relativePathLand.append("kaktus.tga"));
    ImageTga kuh = ImageTga::createCorrectImage(relativePathLand.append("kuh.tga"));
    ImageTga pferd = ImageTga::createCorrectImage(relativePathLand.append("pferd.tga"));
    ImageTga schaf = ImageTga::createCorrectImage(relativePathLand.append("schaf.tga"));
    ImageTga sonnenblume = ImageTga::createCorrectImage(relativePathLand.append("sonnenblume.tga"));
    ImageTga tanne = ImageTga::createCorrectImage(relativePathLand.append("tanne.tga"));
    ImageTga tiger = ImageTga::createCorrectImage(relativePathLand.append("tiger.tga"));
    ImageTga ursus = ImageTga::createCorrectImage(relativePathLand.append("ursus.tga"));


    // images for terrain
    std::string relativePathTerrain = relativePath.append("terrain/");
    ImageTga deep_sea= ImageTga::createCorrectImage(relativePathTerrain.append("deep_sea.tga"));
    ImageTga earth = ImageTga::createCorrectImage(relativePathTerrain.append("earth.tga"));
    ImageTga rocks = ImageTga::createCorrectImage(relativePathTerrain.append("rocks.tga"));
    ImageTga sand = ImageTga::createCorrectImage(relativePathTerrain.append("sand.tga"));
    ImageTga shallow_water = ImageTga::createCorrectImage(relativePathTerrain.append("shallow_water.tga"));
    ImageTga snow = ImageTga::createCorrectImage(relativePathTerrain.append("snow.tga"));

    // images for wasser
    std::string relativePathWasser = relativePath.append("wasser/");
    ImageTga algen = ImageTga::createCorrectImage(relativePathWasser.append("algen.tga"));
    ImageTga delphin = ImageTga::createCorrectImage(relativePathWasser.append("delphin.tga"));
    ImageTga forelle = ImageTga::createCorrectImage(relativePathWasser.append("forelle.tga"));
    ImageTga hai = ImageTga::createCorrectImage(relativePathWasser.append("hai.tga"));
    ImageTga krabbe = ImageTga::createCorrectImage(relativePathWasser.append("krabbe.tga"));
    ImageTga plankton = ImageTga::createCorrectImage(relativePathWasser.append("plankton.tga"));
    ImageTga seetang = ImageTga::createCorrectImage(relativePathWasser.append("seetang.tga"));
    ImageTga wels = ImageTga::createCorrectImage(relativePathWasser.append("wels.tga"));


public:  GameModel();
private: //void loadImages(std::string relativePath); // TODO how to refactor gamemodel class?
    void loadCreatures(std::string relativeFilePath);

};
#endif // GAMEMODEL_H
