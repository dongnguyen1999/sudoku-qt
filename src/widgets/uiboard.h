#ifndef UIBOARD_H
#define UIBOARD_H

#include <QGridLayout>
#include <QWidget>
#include "src/widgets/uicell.h"
#include "src/modules/board.h"

class UICell;
class UIBoard : public QWidget
{
    Q_OBJECT
public:
    explicit UIBoard(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void build();
    QWidget* buildArea(int xArea, int yArea);
    void syncBoard();

    void highLightRCA(Cell cell, bool willHover);
    void turnToEditMode(Cell cell);
    void exitEditMode();
    bool inEditMode();
private:
    Board board;
    UICell* cells[NB_ROWS][NB_COLUMNS];
    QGridLayout* layout;

    //state
    bool onEditing = false;
    Cell editingCell;


signals:

public slots:

};

#endif // UIBOARD_H
