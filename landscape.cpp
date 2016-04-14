/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    landscape
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "landscape.hpp"

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class LandscapeTile /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
LandscapeTile::LandscapeTile() { }

LandscapeTile::LandscapeTile(ClimateType climate) // , QPixmap *climatePixmap
    : climate(climate){ // , climatePixmap(climatePixmap)
    /*if(climate==DEEP_SEA){
        //this->climatePixmap = new QGraphicsPixmapItem(QPixmap::fromImage(gamemodel->shallow_water->qImage, Qt::AutoColor));
    }*/
}



/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class LandscapeGrid /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/

LandscapeGrid::LandscapeGrid() {

}

LandscapeGrid::LandscapeGrid(unsigned int sizeHorizontal, unsigned int sizeVertical,
                             const std::vector<std::vector<LandscapeTile> > &landscapeGridMap)
    : sizeHorizontal(sizeHorizontal), sizeVertical(sizeVertical){}

LandscapeGrid LandscapeGrid::createLandscapeGrid() { // Gamemodel &gamemodel
    LandscapeTile tile1(SHALLOW_WATER);
    LandscapeTile tile2(DEEP_SEA);
    LandscapeTile tile3(SAND);
    LandscapeTile tile4(ROCKS);



    //std::vector<std::vector<LandscapeTile>> landscapeGridMap[2][2];
    LandscapeGrid landscapeGrid = LandscapeGrid();
    // right now I am working with arrays
    landscapeGrid.landscapeTiles[0][0] = tile1;
    landscapeGrid.landscapeTiles[0][1] = tile2;
    landscapeGrid.landscapeTiles[1][0] = tile3;
    landscapeGrid.landscapeTiles[1][1] = tile4;
    landscapeGrid.sizeHorizontal = 2;
    landscapeGrid.sizeVertical = 2;

    //LandscapeGrid(2,2,&landscapeGridMap);
    return landscapeGrid;
}
