#ifndef UICELL_H
#define UICELL_H

#include <QWidget>
#include <QLabel>
#include "src/widgets/uiboard.h"
#include "src/modules/cell.h"
#define NULL_ID -1

class UIBoard;
class Cell;
class UICell : public QWidget
{
    Q_OBJECT
public:
    explicit UICell(Cell cell, UIBoard* parent = 0);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void hoverEnter(QHoverEvent *e);
    void hoverLeave(QHoverEvent *e);
    void showQuestionMark();
    void setHover(bool flag);
    void highLight(bool flag);
    void exitEditMode();
    bool event(QEvent *);
    void mousePressEvent(QMouseEvent *);
private:
    UIBoard* parent;
    Cell cell;
    QWidget* questionIcon;
    QLabel* value;

    //state
    bool onHover = false;
    bool onHighLight = false;
    QColor hoverColor = QColor::fromRgba(qRgba(230,230,230,0.25));
    bool onConflict = false;
    bool onEditing = false;
    int timerId = NULL_ID;
    bool blink = true;
    double questionMarkMargin = 0.2;

signals:

public slots:

};

#endif // UICELL_H
