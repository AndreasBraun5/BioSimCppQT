/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    biosim
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "biosim.hpp"
#include "ui_biosim.h" // generated from biosim.ui form

#include "list"

#include "qmessagebox.h"
#include <qgraphicsscene.h>

#include "gamemodel.hpp"


biosim::biosim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::biosim), // initialisation of the private pointer ui of type biosim              // !delete ui
    gamemodel(new GameModel(qApp->arguments().at(1).toStdString()))                             // !delete gamemodel
{
    ui->setupUi(this);

    // pre selecting of the combobox and its related fields
    tempCreatureEditing =  &gamemodel->creatureList.at(0);
    for(int i=0; i<gamemodel->creatureList.size(); i++){
        ui->creatureEditingComboBox->addItem(QString::fromStdString(gamemodel->creatureList.at(i).creaturename));
    }
    updateCreatureEditLines(tempCreatureEditing);

    // QGraphicsScene scene;
    // scene.addItem(gamemodel->algen);

    connect(ui->creatureEditingComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCreatureComboBox(int)));

    connect(ui->creatureEditingPushButton, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonPause, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonStart, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonStop, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
}

biosim::~biosim()
{
    delete ui;                                                                                  // !delete ui
    delete gamemodel;     // name it gamecontroller                                             // !delete gamemodel
}

void biosim::updateCreatureEditLines(CreatureData const * tempCreatureEditing)
{
    ui->creatureEditingStrengthLineEdit->setText(QString::number(tempCreatureEditing->strength));
    ui->creatureEditingSpeedLineEdit->setText(QString::number(tempCreatureEditing->speed));
    ui->creatureEditingHealthLineEdit->setText(QString::number(tempCreatureEditing->lifetime));
    QString tempProperties;
    for(int i=0; i<tempCreatureEditing->properties.size();i++){
        tempProperties.append(QString::fromStdString(tempCreatureEditing->properties[i]));
        tempProperties.append(" ");
    }
    // TODO what if field to long? also it is editable
    //tempProperties.append("\n");
    //tempProperties.append("asöljfödsajfldsajfdsajölkjfdsa");
    //tempProperties.append("xxxxxxxxxxxxxxxxx");
    ui->creatureEditingPropertiesLineEdit->setText(tempProperties);
}

void biosim::updateCreatureComboBox(int index)
{
    tempCreatureEditing = &gamemodel->creatureList.at(index);
    updateCreatureEditLines(tempCreatureEditing);
}

void biosim::dumbClick()
{
    QMessageBox msg;
    msg.setText("dead end");
    msg.exec();
}







