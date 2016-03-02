/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ #include /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "Main.h"
#include<fstream>
#include <vector>
#include <string>
#include <list>
#include <conio.h>
#include "Creature.h"
#include "TextFileReader.h"
#include "imagetga.h"
#include <exception>
#include "gamemodel.h"
#include <fstream>

#include <QApplication>
//#include <QMainWindow>
//#include <ui_biosim.h>
#include "biosim.h"


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ main /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
int main(int argn, char *argv[]) {

    PRINT(argn);        // number of arguments
    //PRINT(argv[0]);   // argument used by qt
    PRINT(argv[1]);     // relative filepath

    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ Application /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    QApplication a(argn, argv);
    biosim w;
    w.show();
    PRINT("Erfolgreicher Durchlauf\n");
    return a.exec(); // game loop executing
}
