/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    biosim = PRESENTER
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "biosim.hpp"
#include "ui_biosim.h" // generated from biosim.ui form

#include "list"
#include "iostream"

#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>

#include <libnoise/noise.h>

#include "gamemodel.hpp"

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class CreatureData /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
biosim::biosim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::biosim) { // initialisation of the private pointer ui of type biosim             // !delete ui
    ui->setupUi(this);
    try {
        this->gamemodel = new GameModel(qApp->arguments().at(1).toStdString());                 // !delete gamemodel auto managed
        //TODO AB4: gamemodel use this here to initialise landscape = call gamemodel::loadLandscapeGridMap,
        // it is done here because of compiletime determination of size, but up till ignore interaction
        this->gamemodel->loadLandscapeGrid(*gamemodel); // *gamemodel
    } catch(const std::exception &e) {
        writeStartErrorToMsgboxAndExit(e.what());
        exit(EXIT_FAILURE);
    }

    tempCreatureEditing = &gamemodel->creatureDataList.at(0);
    for(int i = 0; i < gamemodel->creatureDataList.size(); i++) {
        ui->creatureEditingComboBox->addItem(QString::fromStdString(gamemodel->creatureDataList.at(i).creaturename));
    }
    updateCreatureEditLines(tempCreatureEditing);

    // scene testing
    QGraphicsScene *scene = new QGraphicsScene(this);                                           // !delete scene auto managed, by parent
    ui->graphicsView->setScene(scene);

    // adding Text
    scene->addText("hello test");

    // adding rectitem
    QGraphicsRectItem tempQRectItem;
    QBrush greenBrush(Qt::green);
    QPen outlinePen(Qt::black);
    tempQRectItem.setRect(0,0,20,40);
    scene->addRect(250,250,50,100,outlinePen,greenBrush);

    // image test
    int size = sqrt((int) gamemodel->sand.size())/2;
    QImage image = QImage(gamemodel->sand.data(), size, size, QImage::Format_ARGB32);
    QGraphicsPixmapItem *testimagepixmap = new QGraphicsPixmapItem(QPixmap::fromImage(image, Qt::AutoColor));
    scene->addItem(testimagepixmap);

    QImage image2 = QImage(gamemodel->delphin.data(), size, size, QImage::Format_ARGB32);
    QGraphicsPixmapItem *testimagepixmap2 = new QGraphicsPixmapItem(QPixmap::fromImage(image2, Qt::AutoColor));
    testimagepixmap2->setOffset(600, 400);
    scene->addItem(testimagepixmap2);

    /*/
     * look up which type the climate is for each tile. Create items and add to the scene with the specified offset, a multiple of 32.
    /*/

    /* for (int i = 0; i <=gamemodel->landscapeGrid.data()->sizeHorizontal; i++) {
         for (int j = 0; j <= gamemodel->landscapeGrid.data()->sizeVertical; j++) {
             QGraphicsPixmapItem *k = new QGraphicsPixmapItem(QPixmap)
         }
     }*/

    // Perlin noise test
    noise::module::Perlin myModule;
    double value = myModule.GetValue(1.25, 0.75, 0.5);
    std::cout << value << std::endl;

    // übergabe der scene an eine Methode/slot updateScene die wiederum updateScene von gamemodel aufruf
    connect(ui->creatureEditingComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCreatureComboBox(int)));
    connect(ui->creatureEditingPushButton, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonPause, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonStart, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonStop, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
}

biosim::~biosim() {
    delete ui;                                                                                  // !delete ui
    //delete gamemodel;                    // TODO                                              // !delete gamemodel automanaged
    //  but there is shown an error if i do that. Deleting an already deleted pointer. Something that qt already does
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
    // TODO Note: Too much text in the LineEdit possible.
    ui->creatureEditingPropertiesLineEdit->setText(tempProperties);
}

void biosim::updateCreatureComboBox(int index) {
    tempCreatureEditing = &gamemodel->creatureDataList.at(index);
    updateCreatureEditLines(tempCreatureEditing);
}

void biosim::dumbClick() {
    QMessageBox msg;
    msg.setText("dead end");
    msg.exec();
}

void biosim::writeStartErrorToMsgboxAndExit(const std::string &error)
{
    QMessageBox msg;
    QString qerror = QString::fromStdString(error);
    msg.setText(qerror);
    msg.exec();
    QApplication::exit();
}
