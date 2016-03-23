/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    read file, read row, split row, check row, create creature,
    storing statistical and error information in data-objects
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef INCLUDED_BIOSIM_TEXTFILEREADER_HPP
#define INCLUDED_BIOSIM_TEXTFILEREADER_HPP

#include <list>

#include "creature.hpp"

class StatisticalFileReadingData;
class ErrorFileReadingData;
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class TextFileReader /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
namespace textFileReader {
// writes information to statisticalFileReadingData & errorFileReadingData
std::list<CreatureData> readCreatureFile(const std::string filepath,
                                         StatisticalFileReadingData &statisticalFileReadingData,
                                         ErrorFileReadingData &errorFileReadingData);

// splitCreaturerow: rowDescription = one row of textfile
void splitCreatureRow(const std::string rowDescription, std::vector<std::string>& tempCreatureInfo);


// correctRow: writes to errorFileReadingData
bool correctRow(const std::vector<std::string>& creatureInfo, StatisticalFileReadingData &statisticalFileReadingData, ErrorFileReadingData &errorFileReadingData);


// splitCreaturerow: cleares the vector creatureInfo
CreatureData createCreatureFromRow(std::vector<std::string>& creatureInfo);
}


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class StatisticalFileReadingData  /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class StatisticalFileReadingData {
public:	int rownumber;
    int rowscorrect;
    int rowsincorrect;
public: StatisticalFileReadingData(){
        rownumber = 0;
        rowscorrect = 0;
        rowsincorrect = 0;
    }
};


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class ErrorFileReadingData /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class ErrorFileReadingData {    
public: int errorInfoCount;
    std::vector<std::string> errorInfo;
public: ErrorFileReadingData(){
        errorInfoCount = 0;
    }
};

#endif // TEXTFILEREADER_HPP
