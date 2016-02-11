/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    read file, read row, split row, check row, create creature,
    storing statistical and error information in data-objects
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#if !defined (INCLUDED_TEXTFILEREADER_H)
#define INCLUDED_TEXTFILEREADER_H


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ #include /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include <list>
#include "Config.h"
#include "Creature.h"

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class TextFileReader /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class TextFileReader {


    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ constructors /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
public: TextFileReader() {}


    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ readCreatureFile: writes information to statisticalFileReadingData &
 *  errorFileReadingData /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
public: std::list<CreatureData> readCreatureFile(const std::string filepath);


    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ splitCreaturerow: rowDescription = one row of textfile  /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
private: void splitCreatureRow(const std::string rowDescription, std::vector<std::string>& tempCreatureInfo);


    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ splitCreaturerow: writes to errorFileReadingData /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
private: bool correctRow(const std::vector<std::string>& creatureInfo);


    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
    /*/ splitCreaturerow: cleares the vector creatureInfo /*/
    /*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
private: CreatureData createCreatureFromRow(std::vector<std::string>& creatureInfo);};


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class TextFileReader, data class /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class StatisticalFileReadingData {
public:	static int rownumber;
    static int rowscorrect;
    static int rowsincorrect;
};


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class TextFileReader, data class /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class ErrorFileReadingData {    
public: static int errorInfoCount;
    static std::vector<std::string> errorInfo;
};

#endif /*/!defined (INCLUDED_TEXTFILEREADER_H)/*/
