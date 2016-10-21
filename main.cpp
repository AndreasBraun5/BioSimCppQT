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
    return a.exec(); // game loop executing
}
// TODO Ab Blatt 5 verwenden der neuen Aufgabenblätter

//Notes: Viewport funktion rect bei Qgraphicsview, bei klick auf scrollbar updaten des sichtbaren bereichs des landscapegrid

// TODO Next: Auslesen des Sichtbaren bereichs, alles außerhalb nicht laden. Signal-Slot um bei scrollbar usage die Bilder nachzuladen
