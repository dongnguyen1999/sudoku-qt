#ifndef UIBOARD_H
#define UIBOARD_H

#include <QGridLayout>
#include <QWidget>
#include "src/widgets/mainwindow.h"
#include <stack>
#include "src/widgets/uicell.h"
#include "src/modules/constrains.h"
#include "src/modules/coord.h"
#include "src/modules/changed.h"
#define DEFAULT_INPUT 1

class UICell;
class UIBoard : public QWidget
{
    Q_OBJECT
public:
    explicit UIBoard(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void init();
    void build();
    QWidget* buildArea(int xArea, int yArea);

    void highLightRCA(Coord position, bool willHover);
    void turnToEditMode(Coord position);
    void callClickedValue(int val);
    void exitEditMode();
    bool inEditMode();
    void hover(UICell* cell, int value, bool flag);
    UICell* select(Coord pos);
    vector<int> getAvailables(Coord position);
    void addConstrains(Coord pos);
    void removeConstrains(Coord pos);
    bool isCorrect();
    void showResult();
    bool hint();
    void undo();
    void startNewGame();
    void showDialog();
    void refresh();

private:
    UICell* cells[NB_ROWS][NB_COLUMNS];
    QGridLayout* layout;
    Constrains constrains;
    stack<Changed> changeHistory;

    int puzzle[NB_ROWS][NB_COLUMNS];
    int result[NB_ROWS][NB_COLUMNS];

    int defaultInput[NB_ROWS][NB_COLUMNS] = {
          {5, 3, 0, 0, 7, 0, 0, 0, 0},
          {6, 0, 0, 1, 9, 5, 0, 0, 0},
          {0, 9, 8, 0, 0, 0, 0, 6, 0},
          {8, 0, 0, 0, 6, 0, 0, 0, 3},
          {4, 0, 0, 8, 0, 3, 0, 0, 1},
          {7, 0, 0, 0, 2, 0, 0, 0, 6},
          {0, 6, 0, 0, 0, 0, 2, 8, 0},
          {0, 0, 0, 4, 1, 9, 0, 0, 5},
          {0, 0, 0, 0, 8, 0, 0, 7, 9},
      };

    //state
    int oldValue;
    bool onEditing = false;
    Coord editingPosition;

    void clearLayout(QLayout*);

signals:

public slots:
    void newGameBtn_clicked();
    void backBtn_clicked();
};

#endif // UIBOARD_H
