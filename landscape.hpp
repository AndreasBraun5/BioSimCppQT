/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    landscape
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef INCLUDED_BIOSIM_LANDSCAPE_HPP
#define INCLUDED_BIOSIM_LANDSCAPE_HPP

#include <vector>

#include "creature.hpp"
//#include "gamemodel.hpp"
class GameModel;

enum ClimateType {DEEP_SEA, EARTH, ROCKS, SAND, SHALLOW_WATER, SNOW};

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class LandscapeTile /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class LandscapeTile{
public: LandscapeTile() = delete;
public: LandscapeTile(ClimateType climate);
public: ClimateType climate;
    bool tileClicked; // check if supported by qt framework? --> equals click or press events
    //std::vector<CreatureData> creatures; // which creatures are on this tile
};

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class LandscapeGrid /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
// capsuling all logic to generate map using perl noise
class LandscapeGrid{
public: LandscapeGrid() = delete;
public: static std::vector<std::vector<LandscapeTile>> createLandscapeGrid
    (unsigned int sizehorizontal, unsigned int sizevertical); //  //TODO AB4: additional parameters at compiletime
};

#endif // LANDSCAPE_HPP
