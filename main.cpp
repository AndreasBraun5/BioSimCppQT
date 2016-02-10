/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "Main.h"

#include<fstream>
#include <vector>
#include <string>
#include <list>
#include <conio.h>

#include "Creature.h"
#include "TextFileReader.h"



/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int main(int argn, char *argv[]) {

    // TODO using namespace std

    // realisation of the relative path of all other data than .../CreatureTable.txt by
    // cutting and concatenating out of its given path from argv[]

    //std::string filename("");	   //works fine, but faster chaning of the two different files
    //for (int i = 1; i < argn; i++) {
    //	filename += argv[i];
    //}
    //
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
