#ifndef UICELL_H
#define UICELL_H

#include <QWidget>
#include "src/widgets/uiboard.h"
#include "src/widgets/styles/cell_styles.h"
#include "src/modules/coord.h"
#include <QLabel>
#define NULL_ID -1

class UIBoard;
class Cell;
class UICell : public QWidget
{
    Q_OBJECT
public:
    explicit UICell(Coord position, UIBoard* parent = 0, int value = 0, bool fixed = false);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void hoverEnter(QHoverEvent *e);
    void hoverLeave(QHoverEvent *e);
    void setValue(int val);
    int getValue();
    void showQuestionMark();
    void showValueLabel();
    void removeQuestionMark();
    void removeValueLabel();
    void highLight(bool flag, QString bodyStyle = "", QString textStyle = "");
    void exitEditMode();
    bool event(QEvent *);
    void mousePressEvent(QMouseEvent *);
    bool isOnConflict();
    bool checkValue(int val);
    void refresh();
private:
    UIBoard* parent;
    Coord position;
    QWidget* questionIcon;
    QLabel* valueLabel;

    //state
    bool enable;
    bool onHighLight = false;
    bool onConflict = false;
    bool onEditing = false;
    int timerId = NULL_ID;
    bool blink = true;
    double questionMarkMargin = 0.2;
    QString bodyStyle = CellStyles::common();
    QString textStyle = CellStyles::valueText(30, Qt::black);

signals:

public slots:

};

#endif // UICELL_H
