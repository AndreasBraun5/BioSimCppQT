/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    main
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <conio.h>                          //################
#include <exception>
#include <fstream>

#include <QApplication>

#include "biosim.hpp"
#include "creature.hpp"
#include "textFileReader.hpp"
#include "imagetga.hpp"
#include "gamemodel.hpp"

// TODO find why creature count not with 0

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ main /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
int main(int argn, char *argv[]) {

    std::cout << argn << "\n";          // number of arguments
    //std::cout << argv[0];             // argument used by qt
    std::cout << argv[1] << "\n";       // relative filepath

    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ Application /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    QApplication a(argn, argv);
    biosim w;
    w.show();
    std::cout << "Erfolgreicher Durchlauf\n";
    return a.exec(); // game loop executing
}
