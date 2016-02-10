/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*/
    read file, read row, split row, check row, create creature,
    storing statistical and error information in data-objects
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#pragma once
#if !defined (INCLUDED_TEXTFILEREADER_H)
#define INCLUDED_TEXTFILEREADER_H

#include <list>

#include "Config.h"
#include "Creature.h"


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
class TextFileReader {

public: TextFileReader() {
    }



        /*/
        Input:			creatureList is used to store the created creatures
        Side effects:	stores information in statisticalFileReadingData [& errorFileReadingData]
        Uses:			splitCreatureRow, correctCreatureRow, createCreatureFromRow
        /*/
public: void readCreatureFile(std::string filepath, std::list<CreatureData>& creatureList);


        /*/
        Input:			rowDescription = one row of textfile, creatureInfo is used to temporary
                        store the splitted creatureInfo of one row
        Side effects:	the actual creature description of one row is stored in creatureInfo
        /*/
private: void splitCreatureRow(std::string rowDescription, std::vector<std::string>& creatureInfo);


        /*/
        Input:			checks the entries from creatureInfo row by row for validity
        Output:			true if the information of one row is valid
        Side effects:	stores information in errorFileReadingData
        /*/
private: bool correctRow(std::vector<std::string>& creatureInfo);


         /*/
         Side effects:	clearing creatureInfo vector
         /*/
private: CreatureData createCreatureFromRow(std::vector<std::string>& creatureInfo);

};


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
class StatisticalFileReadingData {

public:	static int rownumber;
        static int rowscorrect;
        static int rowsincorrect;

};


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
class ErrorFileReadingData {

public: static int errorInfoCount;
        static std::vector<std::string> errorInfo;

};



#endif /*!defined (INCLUDED_TEXTFILEREADER_H)*/
