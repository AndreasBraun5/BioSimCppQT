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
    : sizeHorizontal(sizeHorizontal), sizeVertical(sizeVertical), landscapeGridMap(landscapeGridMap){}

LandscapeGrid LandscapeGrid::createLandscapeGrid(GameModel &gamemodel) { // Gamemodel &gamemodel
    LandscapeTile shallowWaterTile(SHALLOW_WATER);
    LandscapeTile deepSeaTile(DEEP_SEA);
    LandscapeTile sandTile(SAND);
    LandscapeTile rocksTile(ROCKS);

    shallowWaterTile.climatePixmap.reset(gamemodel.shallow_waterPixmap.data());
    deepSeaTile.climatePixmap.reset(gamemodel.deep_seaPixmap.data());
    sandTile.climatePixmap.reset(gamemodel.sandPixmap.data());
    rocksTile.climatePixmap.reset(gamemodel.rocksPixmap.data());

    std::vector<LandscapeTile> row1 = {shallowWaterTile, deepSeaTile};
    std::vector<LandscapeTile> row2 = {sandTile, rocksTile};

    LandscapeGrid landscapeGrid = LandscapeGrid();
    landscapeGrid.sizeHorizontal = 2;
    landscapeGrid.sizeVertical = 2;
    landscapeGrid.landscapeGridMap.push_back(row1);
    landscapeGrid.landscapeGridMap.push_back(row2);

    return landscapeGrid;
}
