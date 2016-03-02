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
    /*/ used for early debugging of work units one and two /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*PRINT("Currently not active any more.\nEnter number: \n 0 for CreatureTable_mitFehlern.txt \n 1 for CreatureTable.txt");
    int integer = 1;
    std::cin >> integer;
    std::string creatureDataFilepath;
    if (integer == 0) {
        creatureDataFilepath = creatureDataFilepath.append("CreatureTable_mitFehlern.txt");
    }
    else {
        creatureDataFilepath = creatureDataFilepath.append("CreatureTable.txt");
    }
    PRINT("");
    */

    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ Application /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    QApplication a(argn, argv);
    biosim w;
    w.show();
    PRINT("Erfolgreicher Durchlauf\n");
    return a.exec(); // game loop executing
}
