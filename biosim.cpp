/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    biosim
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#include "biosim.hpp"
#include "ui_biosim.h" // generated from biosim.ui form

#include "list"
#include "iostream"

#include <qgraphicsscene.h>
#include <qmessagebox.h>
#include <qgraphicsscene.h>
#include <qgraphicsitem.h>
#include <QGraphicsPixmapItem>

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
    } catch(std::exception &e) {
        writeStartErrorToMsgboxAndExit(e.what());
        exit(EXIT_FAILURE);
    }


    // pre selecting of the combobox and its related fields
    tempCreatureEditing =  &gamemodel->creatureList.at(0);
    for(int i = 0; i < gamemodel->creatureList.size(); i++) {
        ui->creatureEditingComboBox->addItem(QString::fromStdString(gamemodel->creatureList.at(i).creaturename));
    }
    updateCreatureEditLines(tempCreatureEditing);

    // TODO AB4: Showing one of the Images
    // TODO Testing Scene
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

    // adding qPixmap of sand.tga, now deep_sea.tga
    QPixmap qPixmap = QPixmap::fromImage(gamemodel->sand->imageData, Qt::ColorOnly);
    scene->addPixmap(qPixmap);

    // or
    /*QGraphicsPixmapItem qPixmapItem;
    qPixmapItem.setPixmap(qPixmap);
    //qPixmapItem.setParentItem(&tempQRectItem); //random selected parent, if scene->addItem the scene takes ownership
    qPixmapItem.setPos(3000,3000);
    bool b = ui->graphicsView->isVisible();
    scene->addItem(&qPixmapItem);
    bool a = qPixmapItem.isVisible(); // it is visible, but won´t be shown */


    //ui->graphicsView->show(); // not needed, hide() works
    //b = ui->graphicsView->isVisible(); // despite being show b is false

    // Testing actual image values
    QImage tempQImage =  gamemodel->sand->imageData;
    std::cout << "Image heigth: " << tempQImage.height() << "\n";
    std::cout << "Image width: " << tempQImage.width() << "\n";
    std::cout << "Image byteCount: " << tempQImage.byteCount() << "\n";
    std::cout << "Image bytesPerLine: " << tempQImage.bytesPerLine() << "\n";
    std::cout << tempQImage.pixelColor(1,1).alpha() << " alpha\n" <<
                 tempQImage.pixelColor(1,1).red() << " red\n" <<
                 tempQImage.pixelColor(1,1).green() << " green\n" <<
                 tempQImage.pixelColor(1,1).blue() << " blue\n";


    connect(ui->creatureEditingComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCreatureComboBox(int)));
    connect(ui->creatureEditingPushButton, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonPause, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonStart, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonStop, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
}

biosim::~biosim() {
    delete ui;                                                                                  // !delete ui
    //delete gamemodel; //TODO Discuss: wanted to delete here,
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
    // TODO Discuss: Too much text in the LineEdit.
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

void biosim::writeStartErrorToMsgboxAndExit(const std::string &error)
{
    QMessageBox msg;
    QString qerror = QString::fromStdString(error);
    //connect(msg, SIGNAL(clicked(bool)),ui , SLOT(updateCreatureComboBox(int)));
    msg.setText(qerror);
    msg.exec();
    QApplication::exit();
}







