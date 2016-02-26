#include "gamemodel.h"
#include "imagetga.h"
#include "textfilereader.h"




GameModel::GameModel()
{
    // TODO change to real relative path
    loadCreatures("F:/Drive/AngewandteInformatik/Bio-SimulatorPraktikum/Elearning/CreatureTable.txt");
}

bool creatureListComparator(const CreatureData cd1, const CreatureData cd2){
    return cd1.getCreaturename()[0] < cd2.getCreaturename()[0];
}

void GameModel::loadCreatures(std::string relativeFilePath)
{
    // TODO working with relative path
    TextFileReader tfr;
    QList<CreatureData> tempList = QList<CreatureData>::fromStdList(tfr.readCreatureFile(relativeFilePath));
    qSort(tempList.begin(), tempList.end(),creatureListComparator);
    creatureList = tempList;
}


