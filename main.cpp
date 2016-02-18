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
#include "imageTga.h"
#include <exception>



/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ main 18.02.16 /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
int main(int argn, char *argv[]) {

    // TODO using namespace std

    // realisation of the relative path of all other data than .../CreatureTable.txt by
    // cutting and concatenating out of its given path from argv[]

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
    creatureList = in.readCreatureFile(filename);



    // identify images to load
    // forall images call constructor Image(imagepath)
    // for testing reasons only open one image at a time
    try{
        //ImageTga testImage {ImageTga::createCorrectImage({"C:/GitHub/BioSimCppQT/GraficsTextfiles/dead.tga"})};
        ImageTga testImage {ImageTga::createCorrectImage({"C:/GitHub/BioSimCppQT/GraficsTextfiles/terrain/sand.tga"})};
    } catch (std::exception& e){
        std::cout << e.what();
    }
    ImageTga testImage {ImageTga::createCorrectImage({"C:/GitHub/BioSimCppQT/GraficsTextfiles/terrain/sand.tga"})};
    PRINT("Aufgabe 1 und Aufgabe 2 erfolgreich beendet.");

    _getch();
    return 0;
}
