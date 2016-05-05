/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    biosim
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

#include "gamemodel.hpp"
#include "landscape.hpp"

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class CreatureData /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
biosim::biosim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::biosim) { // initialisation of the private pointer ui of type biosim             // !delete ui
    ui->setupUi(this);
    try {
        this->gamemodel = new GameModel(qApp->arguments().at(1).toStdString());                 // !delete gamemodel auto managed
        //TODO AB0: gamemodel use this here to initialise landscape = call gamemodel::loadLandscapeGridMap,
        // it is done here because of compiletime determination of size, but up till ignore interaction
        //TODO AB4: additional parameters at compiletime
        this->gamemodel->loadLandscapeGrid(*gamemodel); // *gamemodel
    } catch(const std::exception &e) {
        writeStartErrorToMsgboxAndExit(e.what());
        exit(EXIT_FAILURE);
    }


    // pre selecting of the combobox and its related fields
    //tempCreatureEditing = &gamemodel->creatureList.at(0);
    tempCreatureEditing = &gamemodel->textFileReaderObj.data()->creatureDataQList.at(0);
    //for(int i = 0; i < gamemodel->creatureList.size(); i++) {
    for(int i = 0; i < gamemodel->textFileReaderObj.data()->creatureDataQList.size(); i++) {
        ui->creatureEditingComboBox->addItem(QString::fromStdString(gamemodel->textFileReaderObj.data()->creatureDataQList.at(i).creaturename));
    }
    updateCreatureEditLines(tempCreatureEditing);

    // TODO Test: scene testing
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

    //TODO AB0: only the terrain images are dispayed correctly... header[11] is different, maybe there is the problem
    //TODO AB0: DELETE!? check if items must be deleted

   /* for (int i = 0; i <=gamemodel->landscapeGrid.data()->sizeHorizontal; i++) {
        for (int j = 0; j <= gamemodel->landscapeGrid.data()->sizeVertical; j++) {
            QGraphicsPixmapItem *k = new QGraphicsPixmapItem(QPixmap)
        }
    }*/

    // übergabe der scene an eine Methode/slot updateScene die wiederum updateScene von gamemodel aufruft
    /*QGraphicsPixmapItem x(QPixmap::fromImage(gamemodel->sandImageTga->qImage, Qt::AutoColor));
    x.setOffset(100,100);
    scene->addItem(&x);
    QGraphicsPixmapItem *y = new QGraphicsPixmapItem(QPixmap::fromImage(gamemodel->sandImageTga->qImage, Qt::AutoColor));
    y->setOffset(100,100);
    y->setOpacity(1.0);
    scene->addItem(y);
    QGraphicsPixmapItem *z = new QGraphicsPixmapItem(QPixmap::fromImage(gamemodel->birne->qImage, Qt::AutoColor));
    z->setOffset(200,200);
    scene->addItem(z);*/

    /*LandscapeGrid *landscape2 = gamemodel->landscapeGrid.data();
    LandscapeTile landscapeTile1 = landscape2->landscapeGridMap[0][0];
    QPixmap *pixmapTile1 = landscapeTile1.climatePixmap.data();
    QGraphicsPixmapItem *k = new QGraphicsPixmapItem(*pixmapTile1);
    k->setOffset(0,0);
    scene->addItem(k);

    QGraphicsPixmapItem *m = new QGraphicsPixmapItem(gamemodel->sandBlankPixmap);
    m->setOffset(-50,50);
    scene->addItem(m);*/

    // Item generation here because
    /*QGraphicsPixmapItem *u = new QGraphicsPixmapItem (*gamemodel->landscapeGrid.data()->landscapeGridMap[0][0].climatePixmap.data());
    u->setOffset(110,110);
    u->setOpacity(0.5);
    scene->addItem(u);*/



    //ui->graphicsView
    /* schwachsinn
    QPixmap *pix = new QPixmap(QPixmap::fromImage(gamemodel->birne->qImage, Qt::AutoColor));
    QPainter qPainter(pix);
    qPainter.setRenderHint(QPainter::Antialiasing);
    scene->render(&qPainter);*/

    connect(ui->creatureEditingComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCreatureComboBox(int)));
    connect(ui->creatureEditingPushButton, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonPause, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonStart, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonStop, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
}

biosim::~biosim() {
    delete ui;                                                                                  // !delete ui
    //delete gamemodel;                    // TODO                                              // !delete gamemodel automanaged
    //  but there is shown an error if i do that. Deleting an already deleted pointer.
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
    // TODO Note: Too much text in the LineEdit.
    ui->creatureEditingPropertiesLineEdit->setText(tempProperties);
}

void biosim::updateCreatureComboBox(int index) {
    tempCreatureEditing = &gamemodel->textFileReaderObj.data()->creatureDataQList.at(index);
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
