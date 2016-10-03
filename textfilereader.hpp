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
// namespace vs class: lookup regeln, koeniglookup
class textFileReader {

public: textFileReader() = delete;

// writes information to statisticalFileReadingData & errorFileReadingData
static std::list<CreatureData> readCreatureFile(const std::string &filePath);

// splitCreaturerow: rowDescription = one row of textfile, writes to tempCreatureInfo
static void splitCreatureRow(const std::string &rowDescription,
                      std::vector<std::string> &tempCreatureInfo);

// correctRow: writes to errorFileReadingData
static bool correctRow(const std::vector<std::string> &creatureInfo,
                StatisticalFileReadingData &statisticalFileReadingData,
                ErrorFileReadingData &errorFileReadingData);

// splitCreaturerow: cleares the vector creatureInfo
static CreatureData createCreatureFromRow(std::vector<std::string> &creatureInfo);
};


/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class StatisticalFileReadingData  /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
class StatisticalFileReadingData {
public:	int rownumber;
    int rowscorrect;
    int rowsincorrect;

    StatisticalFileReadingData() {
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
    ErrorFileReadingData() {
        errorInfoCount = 0;
    }
};

#endif // TEXTFILEREADER_HPP
