/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*
    .cpp-file is always orderd as following:			see book: one definition rule
    function implementation
    definition of global objects
    definition and initialisation of global constants:	extern const int GLOBALE_KONSTANTE = 1;
*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "Main.h"

#include<fstream>
#include <vector>
#include <string>
#include <list>
#include <conio.h>

#include "Creature.h"
#include "TextFileReader.h"
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int main(int argn, char *argv[]) {


    //std::string filename("");	   //works fine, but faster chaning of the two different files
    //for (int i = 1; i < argn; i++) {
    //	filename += argv[i];
    //}
    // /*
    PRINT("Enter number: \n 0 for CreatureTable_mitFehlern.txt \n 1 for CreatureTable.txt");
    int integer = 1;
    std::cin >> integer;
    std::string filename;
    if (integer == 0) {
        filename = "F:/Drive/AngewandteInformatik/Bio-SimulatorPraktikum/Elearning/CreatureTable_mitFehlern.txt";
    }
    else {
        filename = "F:/Drive/AngewandteInformatik/Bio-SimulatorPraktikum/Elearning/CreatureTable.txt";
    }
    PRINT("");

    std::list<CreatureData> creatureList; // stores all the creature objects
    TextFileReader in{};
    in.readCreatureFile(filename, creatureList);

    _getch();
    return 0;
}
