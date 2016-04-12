/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    main
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <exception>
#include <fstream>

#include <QApplication>

#include "biosim.hpp"
#include "creature.hpp"
#include "textFileReader.hpp"
#include "imagetga.hpp"
#include "gamemodel.hpp"

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
    std::cout << "\nErfolgreicher Durchlauf\n";
    return a.exec(); // game loop executing
}
