/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    class biosim is subclass of QMainWindow and Ui_biosim. Equals the presenter.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef BIOSIM_H
#define BIOSIM_H

#include <QMainWindow>
#include "gamemodel.h" // had circular dependency
#include "creature.h"

namespace Ui {
class biosim;
}

class biosim : public QMainWindow
{
    Q_OBJECT

public:
    explicit biosim(QWidget *parent = 0);
    ~biosim();
    void updateCreatureEditLines(CreatureData tempCreatureEditing);
    CreatureData getTempCreatureEditing() const;

private:
    CreatureData tempCreatureEditing;
    Ui::biosim *ui;
    GameModel *gamemodel; // TODO access violation

private slots:
    void updateCreatureComboBox(int index);
    void dumbClick();

};

#endif // BIOSIM_H
