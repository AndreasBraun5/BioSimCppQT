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
#include <QScrollBar>
#include <QResizeEvent>

#include "gamemodel.hpp"

void QGraphicsView::resizeEvent(QResizeEvent *event){
    QSize newQSize = event->size();
    int height = newQSize.height();
    int width = newQSize.width();
    int newSize = 500; // default value, so that the programm does´t crash
    if(height >= width){
        newSize = height;
    } else {
        newSize = width;
    }
    biosim::updateVisibleScene(newSize);
}

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class CreatureData /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
biosim::biosim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::biosim) { // initialisation of the private pointer ui of type biosim             // !delete ui
    ui->setupUi(this);
    try {
        this->gamemodel = new GameModel(qApp->arguments().at(1).toStdString());                 // !delete gamemodel auto managed
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

    int qrectfSize = 500*32; // TODO AB4: Needs to be sizehorizontal*sizeoftile
    QRectF viewQrectf (0,0,qrectfSize,qrectfSize); // Constructs a rectangle with (x, y) as its top-left corner and the given width and height.
    ui->graphicsView->setSceneRect(viewQrectf);

    // image test
    int size = sqrt((int) gamemodel->sand.size())/2;
    QImage image = QImage(gamemodel->sand.data(), size, size, QImage::Format_ARGB32);
    QGraphicsPixmapItem *testimagepixmap = new QGraphicsPixmapItem(QPixmap::fromImage(image, Qt::AutoColor));
    scene->addItem(testimagepixmap);

    QImage image2 = QImage(gamemodel->delphin.data(), size, size, QImage::Format_ARGB32);
    QGraphicsPixmapItem *testimagepixmap2 = new QGraphicsPixmapItem(QPixmap::fromImage(image2, Qt::AutoColor));
    testimagepixmap2->setOffset(600, 400);
    scene->addItem(testimagepixmap2);

    QRect viewport_rect(0, 0, ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height());
    QRectF visible_scene_rect = ui->graphicsView->mapToScene(viewport_rect).boundingRect();

    ui->graphicsView->viewport();

    QScrollBar *horizontalScrollbar = ui->graphicsView->horizontalScrollBar();
    QScrollBar *verticalScrollbar =  ui->graphicsView->verticalScrollBar();

    int horizontalvalue = horizontalScrollbar->value();
    int verticalvalue = verticalScrollbar->value();


    /*/
     * creating "empty" QGraphicsScene with specified size.
     *
     * calculating the visible area of the QGraphicsScene scence within the QGraphicsView graphicsView.
     *
     * "Rendering" = adding QGraphicsPixmapItems to the visible scene area plus one or two more at the border
     * and deleting no more visible, needed items if being scolled using a event.
     *
     *
     * fixed size needed? the solution is to maybe use a change size event
     *
     * zooming?
    /*/

    /*/
     * look up which type the climate is for each tile. Create items and add to the scene with the specified offset, a multiple of 32.
    /*/
    QImage deep_sea = QImage(gamemodel->deep_sea.data(), size, size, QImage::Format_ARGB32);
    QImage shallow_water = QImage(gamemodel->shallow_water.data(), size, size, QImage::Format_ARGB32);
    QImage sand = QImage(gamemodel->sand.data(), size, size, QImage::Format_ARGB32);
    QImage earth = QImage(gamemodel->earth.data(), size, size, QImage::Format_ARGB32);
    QImage rocks = QImage(gamemodel->rocks.data(), size, size, QImage::Format_ARGB32);
    QImage snow = QImage(gamemodel->snow.data(), size, size, QImage::Format_ARGB32);

    QPixmap deep_seaPixmap = QPixmap::fromImage(deep_sea, Qt::AutoColor);
    QPixmap emptyPixmap = QPixmap();
    QGraphicsPixmapItem *deep_seaPixmapItem = new QGraphicsPixmapItem(deep_seaPixmap);
    //QGraphicsPixmapItem *deep_seaPixmap = new QGraphicsPixmapItem(QPixmap::fromImage(deep_sea, Qt::AutoColor));

    // /*/ Temporary drawing one fourth of the size
    for (int i = 0; i < this->gamemodel->landscapeGridmap.size()/4; i++) {
        for (int j = 0; j < this->gamemodel->landscapeGridmap[i].size()/4; j++) {
            QImage tempImage;
            if(this->gamemodel->landscapeGridmap[i][j].climate == DEEP_SEA)
                {tempImage = deep_sea;}
            else if(this->gamemodel->landscapeGridmap[i][j].climate == SHALLOW_WATER){tempImage = shallow_water;}
            else if(this->gamemodel->landscapeGridmap[i][j].climate == SAND){tempImage = sand;}
            else if(this->gamemodel->landscapeGridmap[i][j].climate == EARTH){tempImage = earth;}
            else if(this->gamemodel->landscapeGridmap[i][j].climate == ROCKS){tempImage = rocks;}
            else //this->gamemodel->landscapeGridmap[i][j].climate == SNOW)
                {tempImage = snow;}
            //scene->addPixmap(QPixmap::fromImage(tempImage, Qt::AutoColor)); // Coordinates are default (0,0)
            QGraphicsPixmapItem *tempPixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(tempImage, Qt::AutoColor));
            tempPixmapItem->setOffset(i*32,j*32);
            scene->addItem(tempPixmapItem);
         }
    }
    // /*/
    /*/
    for (int i = 0; i < this->gamemodel->landscapeGridmap.size(); i++) {
            for (int j = 0; j < this->gamemodel->landscapeGridmap[i].size(); j++) {
                QGraphicsPixmapItem *tempPixmapitem = new QGraphicsPixmapItem(emptyPixmap);
                tempPixmapitem->setOffset(i*32,j*32);
                scene->addItem(tempPixmapitem);
             }
    }
    /*/
    //QImage z = QImage();
    //QGraphicsPixmapItem *zz = new QGraphicsPixmapItem(QPixmap::fromImage(z, Qt::AutoColor));
    //scene->addItem(zz);
    // */

    /*/
    QImage tempImage = QImage(32, 32, QImage::Format_ARGB32);
    QPixmap tempPixmap = QPixmap::fromImage(tempImage, Qt::AutoColor);
    for (int i = 0; i < this->gamemodel->landscapeGridmap.size()/4; i++) {                          // gerade viertel so groß
            for (int j = 0; j < this->gamemodel->landscapeGridmap[i].size()/4; j++) {
                QGraphicsPixmapItem *tempPixmapItem = new QGraphicsPixmapItem(tempPixmap);
                tempPixmapItem->setOffset(i*32+320,j*32+320);
                scene->addItem(tempPixmapItem);
             }
    }
    /*/










    // adding Text
    scene->addText("hello test");

    // adding rectitem
    QGraphicsRectItem tempQRectItem;
    QBrush greenBrush(Qt::green);
    QPen outlinePen(Qt::black);
    tempQRectItem.setRect(0,0,20,40);
    scene->addRect(250,250,50,100,outlinePen,greenBrush);

    // übergabe der scene an eine Methode/slot updateScene die wiederum updateScene von gamemodel aufruft
    connect(ui->creatureEditingComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCreatureComboBox(int)));
    connect(ui->creatureEditingPushButton, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonPause, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonStart, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->simulationControllButtonStop, SIGNAL(clicked(bool)), this, SLOT(dumbClick()));
    connect(ui->graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateVisibleSceneScrollbar(int)));
    connect(ui->graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateVisibleSceneScrollbar(int)));
    //connect(ui->graphicsView->resizeEvent(QResizeEvent *event), SIGNAL(), this, SLOT(updateVisibleScene(int)));
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
//
void biosim::updateVisibleSceneScrollbar(int value) {
    // always updating everything
    // computing visible area: graphicsViewSize, maximum value, scrollbarValue (value) --> position,
    // clearing vs. keeping the most
    // filling a bit more tiles than needed,
    std::cout << "\nvalue: " << value << "" << std::endl;
    std::cout << "maxValue: " << ui->graphicsView->horizontalScrollBar()->maximum() << std::endl;
    std::cout << "heightView: " << ui->graphicsView->height() << std::endl;
    std::cout << "widthView: " << ui->graphicsView->width() << std::endl;
}

// TODO delete
void biosim::updateVisibleSceneMouseDrag(int newSceneSize, int oldScenceSize) {
    std::cout << "newSizeValue: " << newSceneSize << std::endl;
    std::cout << "oldSizeValue: " << oldScenceSize << std::endl;
}

void biosim::updateVisibleScene(int squareSize) {
    std::cout << "Current squareSize: " << squareSize << std::endl;
}

void biosim::writeStartErrorToMsgboxAndExit(const std::string &error) {
    QMessageBox msg;
    QString qerror = QString::fromStdString(error);
    msg.setText(qerror);
    msg.exec();
    QApplication::exit();
}
