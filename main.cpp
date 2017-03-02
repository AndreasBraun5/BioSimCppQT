/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    main: input of console parameters.
    creation of an QApplication object that handles the game loop and other stuff.
    creation of biosim object that is our mainwindow = PRESENTER
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <exception>
#include <fstream>

#include <QApplication>
#include <QMessageBox>

#include "biosim.hpp"
#include "creature.hpp"
#include "textFileReader.hpp"
#include "imagetga.hpp"
#include "gamemodel.hpp"

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ main /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
int main(int argn, char *argv[]) {

    //TODO Note: error handling if not enough console parameters are given
    std::cout << argn << "\n";          // number of arguments
    //std::cout << argv[0];             // argument used by qt
    std::cout << argv[1] << "\n";       // relative filepath

    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ Application /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    QApplication a(argn, argv);
    biosim w;
    w.show();
    std::cout << "\nErfolgreicher Durchlauf\n";
    w.updateVisibleScene(); // Needed to correctly initialise, or else you have only 4 tiles
    // in the scene, it has got something to do with the init order of the different elements
    return a.exec(); // game loop executing
}

// TODO: All stuff to do for AB5

// TODO Note: all creatures that are added here must be the same (or only a reference/pointer) that are stored in the gamemodel.

// TODO: deletin a creature in the gamemodel must result in deleting the creature on the tile and vice versa

// TODO Discuss: Now I have the same Creatures for the Possible Creatures and the Creature Objects being placed onto the grid.

// TODO Discuss: make map["key"] with enum, well only practicable for the tiles via using an extra std::map<int, QImage>. But why to do so?
