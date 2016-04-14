/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    landscape
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef INCLUDED_BIOSIM_LANDSCAPE_HPP
#define INCLUDED_BIOSIM_LANDSCAPE_HPP

#include <vector>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include "creature.hpp"

enum ClimateType {DEEP_SEA, EARTH, ROCKS, SAND, SHALLOW_WATER, SNOW};

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class LandscapeTile /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class LandscapeTile{
//public: LandscapeTile() = delete;
public: LandscapeTile();
public: LandscapeTile(ClimateType climate); // , QPixmap *climatePixmap
public: ClimateType climate;
    bool tileClicked; // check if supported by qt framework? --> equals click or press events
    QSharedPointer<QPixmap> climatePixmap;
    //std::vector<CreatureData> creatures; Oder gespeichert in der Creature? eher nicht...
    //QScopedPointer<QGraphicsPixmapItem> climatePixmap;
    // ?shared pointer" to one or more living creatures holded in gamemodel
    // one or more creatures allowed on it
};

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class LandscapeGrid /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
// capsuling all logic to generate map using perl noise
class LandscapeGrid{
//public: LandscapeGrid() = delete;
public: LandscapeGrid();
public: LandscapeGrid(unsigned int sizeHorizontal, unsigned int sizeVertical,
                       const std::vector<std::vector<LandscapeTile>> &landscapeGridMap);
public: unsigned int sizeHorizontal; // const
    unsigned int sizeVertical; // const
    //const std::vector<std::vector<LandscapeTile>> landscapeGridMap; // landscapeGridmap [down][left] = landscapeGridmap [0][0]
    LandscapeTile landscapeTiles[2][2]; // tiles, working with arrays better here
    static LandscapeGrid createLandscapeGrid(); //  //TODO AB4: additional parameters at compiletime
    // 2 dim grid vector containing all QGraphicsPixmapItems with specified offsets.
    // They are then added by the scene with a loop
    // size of landscape: Not hardcoded. Should be appropiatetly selected during compile time
};



#endif // LANDSCAPE_HPP
