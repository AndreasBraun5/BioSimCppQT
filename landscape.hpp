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

class GameModel;

enum ClimateType {DEEP_SEA, EARTH, ROCKS, SAND, SHALLOW_WATER, SNOW};

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class LandscapeTile /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class LandscapeTile{
public: LandscapeTile() = delete;
public: LandscapeTile(ClimateType climate);
public: ClimateType climate; // TODO Discuss: const ...  // "operator = function" is unavailable in Landscapetile. Need to implement myself...
    //std::vector<CreatureData> creatures; // This way it is intended to memorize which creatures are on this tile
};

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class LandscapeGrid /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class LandscapeGrid{
public: LandscapeGrid() = delete;
public: static std::vector<std::vector<LandscapeTile>> createLandscapeGrid
    (unsigned int sizehorizontal, unsigned int sizevertical);
};

#endif // LANDSCAPE_HPP
