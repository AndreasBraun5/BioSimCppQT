/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
/*/
    class biosim is subclass of QMainWindow and Ui_biosim. Equals the presenter.
/*/
/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
#pragma once
#ifndef INCLUDED_BIOSIM_BIOSIM_HPP
#define INCLUDED_BIOSIM_BIOSIM_HPP

#include <QMainWindow>

#include "gamemodel.hpp" // had circular dependency
#include "creature.hpp"

/*/+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/*/
namespace Ui {
class biosim;
}

class biosim : public QMainWindow
{
    Q_OBJECT

public:
    explicit biosim(QWidget *parent = 0);
    ~biosim();
    void updateCreatureEditLines(const CreatureData *tempCreatureEditing);
    CreatureData getTempCreatureEditing() const;

private:
    CreatureData const * tempCreatureEditing; // pointer to const object
    Ui::biosim *ui;
    GameModel *gamemodel; // TODO access violation scoped pointer?

private slots:
    void updateCreatureComboBox(int index);
    void dumbClick();

};

#endif // BIOSIM_HPP
