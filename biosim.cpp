/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/

/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "biosim.h"
#include "ui_biosim.h" // generated from biosim.ui form
#include "gamemodel.h"
#include "list"
#include "qmessagebox.h"

biosim::biosim(QWidget *parent) :
    QMainWindow(parent), // constructor call to parent class
    ui(new Ui::biosim) // initialisation of the private pointer ui of type biosim
{
    ui->setupUi(this);

    // pre selecting of the combobox and its related fields
    tempCreatureEditing = gamemodel.creatureList.at(0); // TODO Now tempCreatureEditing points to the same object??
    for(int i=0; i<gamemodel.creatureList.size(); i++){
        ui->creatureEditingComboBox->addItem(QString::fromStdString(gamemodel.creatureList.at(i).getCreaturename()));
    }
    updateCreatureEditLines(tempCreatureEditing); // initally to the first element

    connect(ui->creatureEditingComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCreatureComboBox(int)));
    connect(ui->creatureEditingPushButton, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonPause, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonStart, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonStop, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
}

biosim::~biosim()
{
    delete ui;
}

void biosim::updateCreatureEditLines(CreatureData tempCreatureEditing)
{
    ui->creatureEditingStrengthLineEdit->setText(QString::number(tempCreatureEditing.getStrength()));
    ui->creatureEditingSpeedLineEdit->setText(QString::number(tempCreatureEditing.getSpeed()));
    ui->creatureEditingHealthLineEdit->setText(QString::number(tempCreatureEditing.getLifetime()));
    QString tempProperties;
    for(int i=0; i<tempCreatureEditing.getProperties().size();i++){
        tempProperties.append(QString::fromStdString(tempCreatureEditing.getProperties()[i]));
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
    tempCreatureEditing = gamemodel.creatureList.at(index);
    updateCreatureEditLines(tempCreatureEditing);
}

void biosim::dumbClick()
{
    QMessageBox msg;
    msg.setText("dead end");
    msg.exec();
}







