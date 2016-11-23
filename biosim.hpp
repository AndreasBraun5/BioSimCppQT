/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    biosim = PRESENTER. class biosim is subclass of QMainWindow and Ui_biosim. Equals the PRESENTER,
    which in this case holds an pointer to the VIEW which is generated out of the
    biosim.ui file.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef INCLUDED_BIOSIM_BIOSIM_HPP
#define INCLUDED_BIOSIM_BIOSIM_HPP

#include <QMainWindow>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <map>

#include "gamemodel.hpp"
#include "creature.hpp"

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/ class CreatureData /*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
namespace Ui {
class biosim;
class GridCursorCallback;
}

// capsuling the callback into a abstract class
class GridCursorCallback {
public:
    virtual void gridClicked(int xCoord, int yCoord) = 0;
};

class GridClickablePixmapItem : public QGraphicsPixmapItem {
public :
    GridClickablePixmapItem() = delete;
    GridClickablePixmapItem(const QPixmap &pixmap, int x, int y,
                            GridCursorCallback *cursorCallback = NULL, QGraphicsItem *parent = Q_NULLPTR);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    double opacity;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    GridCursorCallback *cursorCallback;
    int x;
    int y;
};

class biosim : public QMainWindow, public virtual GridCursorCallback {
    Q_OBJECT

public:
    explicit biosim(QWidget *parent = 0);
    ~biosim();
    void loadQImages();
    void updateCreatureEditLines(const Creature *tempCreatureEditing);
    void writeStartErrorToMsgboxAndExit(const std::string &error);
    void updateVisibleScene();
    void resizeEvent(QResizeEvent *event);
    virtual void gridClicked(int xCoord, int yCoord);
    //void biosim::paintEvent(QPaintEvent *);

private:
    Creature const *tempCreatureEditing;
    Ui::biosim *ui;
    QGraphicsScene *scene;
    int imageSizeInPixel = 32;
    // TODO Discuss: access violation scoped pointer, if main window is closed. Solved?: the pointer gamemodel was
    // deleted in the constructor, analog to the ui pointer. But I blieve some kind of garbage collection tried
    // again to delete the already deleted pointer gamemodel. How to check if the gamemodel pointer is really already deleted?
    // or better use smart pointer?
    GameModel *gamemodel;
    // TODO Discuss: Improvement, name it gamecontroller
    // Model(gamemodel)-View(Ui_biosim.h)-Presenter(biosim-.hpp/.cpp) intended. Gamemodel doesn´t know of
    // Ui_biosim.h (generated from biosim.ui) and biosim-.hpp/.cpp. Gamemodel will contain all data and logic. biosim will
    // handle the communication and Ui_biosim will only contain the view.

    std::map<std::string, QImage> qImageMap;
    int cursorX = 0;
    int cursorY = 0;


private slots:
    void updateCreatureComboBox(int index);
    void dumbClick();
    void placeCreature();

public slots:
    void updateVisibleSceneScrollbar();
};

#endif // BIOSIM_HPP
