/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    biosim
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "biosim.hpp"
#include "ui_biosim.h" // generated from biosim.ui form

#include "list"
#include "iostream"

#include "qmessagebox.h"
#include <qgraphicsscene.h>

#include "gamemodel.hpp"

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class CreatureData /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
biosim::biosim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::biosim) // initialisation of the private pointer ui of type biosim              // !delete ui
    {                           // !delete gamemodel
    ui->setupUi(this);
    // TODO Discussion: Application doesn´t start if a vital part couldn´t be loaded, up till now images.
    // TODO Unfinished: Excercise 3: Open Window and tell if image is loaded wrong (done), if Textfile is loaded wrong (still missing)
    try {
        this->gamemodel = new GameModel(qApp->arguments().at(1).toStdString());
    } catch(std::exception &e) {
        startError(e.what());
        exit(EXIT_FAILURE);
    }


    // pre selecting of the combobox and its related fields
    tempCreatureEditing =  &gamemodel->creatureList.at(0);
    for(int i = 0; i < gamemodel->creatureList.size(); i++) {
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

biosim::~biosim() {
    delete ui;                                                                                  // !delete ui
    //delete gamemodel; TODO Discuss: wanted to delete here,
    //  but there is shown an error if i do that. Deleting an already deleted pointer. // !delete gamemodel
}

void biosim::updateCreatureEditLines(const CreatureData *tempCreatureEditing) {
    ui->creatureEditingStrengthLineEdit->setText(QString::number(tempCreatureEditing->strength));
    ui->creatureEditingSpeedLineEdit->setText(QString::number(tempCreatureEditing->speed));
    ui->creatureEditingHealthLineEdit->setText(QString::number(tempCreatureEditing->lifetime));
    QString tempProperties;
    for(int i = 0; i < tempCreatureEditing->properties.size();i++) {
        tempProperties.append(QString::fromStdString(tempCreatureEditing->properties[i]));
        tempProperties.append(" ");
    }
    // TODO Discuss: what if field to long? also it is editable
    //tempProperties.append("\n");
    //tempProperties.append("asöljfödsajfldsajfdsajölkjfdsa");
    //tempProperties.append("xxxxxxxxxxxxxxxxx");
    ui->creatureEditingPropertiesLineEdit->setText(tempProperties);
}

void biosim::updateCreatureComboBox(int index) {
    tempCreatureEditing = &gamemodel->creatureList.at(index);
    updateCreatureEditLines(tempCreatureEditing);
}

void biosim::dumbClick() {
    QMessageBox msg;
    msg.setText("dead end");
    msg.exec();
}

void biosim::startError(const std::string &error)
{
    QMessageBox msg;
    QString qerror = QString::fromStdString(error);
    //connect(msg, SIGNAL(clicked(bool)),ui , SLOT(updateCreatureComboBox(int)));
    msg.setText(qerror);
    msg.exec();
    QApplication::exit();
}







