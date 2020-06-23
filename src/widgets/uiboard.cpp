#include "src/widgets/uiboard.h"
#include <QDebug>
#include <QGridLayout>
#include <QStyleOption>
#include <QPainter>
#include <QDialog>
#include <QPushButton>
#include "src/widgets/styles/cell_styles.h"
int counter1 = 0;

UIBoard::UIBoard(QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout;
    layout->setMargin(8);
    layout->setHorizontalSpacing(4);
    layout->setVerticalSpacing(4);
    setLayout(layout);
    startNewGame(DEFAULT_INPUT);
}

void UIBoard::init() {
    constrains.clear();
    for (int i = 0; i < NB_ROWS; i++) {
        for (int j = 0; j < NB_COLUMNS; j++) {
            cells[i][j] = new UICell(Coord(i,j), this, inputs[i][j], inputs[i][j] != EMPTY);
            addConstrains(Coord(i,j));
        }
    }
}

void UIBoard::paintEvent(QPaintEvent *) {
//    qDebug() << "paint event " << counter1++;
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void UIBoard::build() {
    clearLayout(layout);
    for (int i = 0; i < AREA_SQUARE_SIZE; i++) {
        for (int j = 0; j < AREA_SQUARE_SIZE; j++) {
            QWidget* area = buildArea(i,j);
            layout->addWidget(area, i, j);
        }
    }
}

QWidget* UIBoard::buildArea(int xArea, int yArea) {
    QWidget* widget = new QWidget();
    widget->setStyleSheet("background-color: #b1ebf1;");
    QGridLayout *gridLayout = new QGridLayout;
    for (int i = 0; i < AREA_SQUARE_SIZE; i++) {
        for (int j = 0; j < AREA_SQUARE_SIZE; j++) {
            gridLayout->addWidget(cells[AREA_SQUARE_SIZE*xArea+i][AREA_SQUARE_SIZE*yArea+j], i, j);
        }
    }
    gridLayout->setMargin(5);
    gridLayout->setHorizontalSpacing(2);
    gridLayout->setVerticalSpacing(2);
    widget->setLayout(gridLayout);
    return widget;
}

void UIBoard::highLightRCA(Coord position, bool willHover) {
    int row = position.x, column = position.y;
    UICell* cell = cells[row][column];
    int value = cell->getValue();
    for (int i = 0; i < NB_COLUMNS; i++) {
        UICell* otherCell = cells[row][i];
        hover(otherCell, value, willHover);
    }
    for (int i = 0; i < NB_ROWS; i++) {
        UICell* otherCell = cells[i][column];
        hover(otherCell, value, willHover);
    }
    int xArea = row/AREA_SQUARE_SIZE, yArea = column/AREA_SQUARE_SIZE;
    for (int i = 0; i < AREA_SQUARE_SIZE; i++) {
        for (int j = 0; j < AREA_SQUARE_SIZE; j++) {
            UICell* otherCell = cells[AREA_SQUARE_SIZE*xArea+i][AREA_SQUARE_SIZE*yArea+j];
            hover(otherCell, value, willHover);
        }
    }
    cell->highLight(false);
    if (!cell->isOnConflict()) cell->highLight(willHover, CellStyles::hover(), CellStyles::valueText(30, Qt::black));
    else cell->highLight(willHover, CellStyles::hoverError(), CellStyles::valueText(30, Qt::black));
}

void UIBoard::turnToEditMode(Coord position) {
    onEditing = true;
    editingPosition = position;
    highLightRCA(position, true);
    oldValue = select(position)->getValue();
}

bool UIBoard::inEditMode() {
    return onEditing;
}

void UIBoard::exitEditMode() {
    if (inEditMode()) {
        onEditing = false;
        cells[editingPosition.x][editingPosition.y]->exitEditMode();
        highLightRCA(editingPosition, false);
        int newValue = select(editingPosition)->getValue();
        if (newValue != oldValue) changeHistory.push(Changed(editingPosition, oldValue, newValue));
        if (isCorrect()) showDialog();
    }
}

void UIBoard::callClickedValue(int val) {
    if (onEditing) {
        cells[editingPosition.x][editingPosition.y]->setValue(val);
    }
}

void UIBoard::hover(UICell *cell, int value, bool flag) {
    QString bodyStyle = CellStyles::border(Qt::black, 2) +
            CellStyles::highLight(QColor::fromRgba(qRgba(230,230,230,0.2)));
    QString textStyle = CellStyles::valueText(30, Qt::black);
    QString errorStyle = CellStyles::border(Qt::red, 2) +
            CellStyles::highLight(QColor::fromRgba(qRgba(230,230,230,0.2)));
    if (value != EMPTY && value == cell->getValue())
        cell->highLight(flag, errorStyle, textStyle);
    else cell->highLight(flag, bodyStyle, textStyle);
}

void UIBoard::startNewGame(bool defaultInp) {
    if (defaultInp) {
        for (int i = 0; i < NB_ROWS; i++) {
          for (int j = 0; j < NB_COLUMNS; j++) {
              inputs[i][j] = defaultInput[i][j];
          }
        }
    } else {
        for (int i = 0; i < NB_ROWS; i++) {
          for (int j = 0; j < NB_COLUMNS; j++) {
              inputs[i][j] = EMPTY;
          }
        }
        for (int k = 0; k < 30; k++) {
          Coord position;
          int value;
          do {
            position = Coord(random(NB_ROWS),random(NB_COLUMNS));
          } while (inputs[position.x][position.y] != EMPTY);
          do {
              value = random(10);
          } while (!checkInputValue(position, value));
          inputs[position.x][position.y] = value;
        }
    }
    init();
    build();
}

bool UIBoard::isCorrect() {
    for (int i = 0; i < NB_ROWS; i++) {
        for (int j = 0; j < NB_ROWS; j++) {
            if (cells[i][j]->getValue() == EMPTY || cells[i][j]->isOnConflict()) {
                return false;
            }
        }
    }
    return true;
}

vector<int> UIBoard::sort(vector<int> availables, int valueCount[]) {
  for (int i = 0; i < availables.size(); i++) {
    for (int j = i; j < availables.size(); j++) {
      if (valueCount[availables[i]] > valueCount[availables[j]]) {
        int t = availables[i];
        availables[i] = availables[j];
        availables[j] = t;
      }
    }
  }
  return availables;
}

bool UIBoard::hint() {
    if (isCorrect()) return false;
    int min = INF;
    Coord hintPos;
    int valueCount[MAX_VALUE] = {};
    for (int i = 0; i < NB_ROWS; i++) {
        for (int j = 0; j < NB_ROWS; j++) {
            if (cells[i][j]->getValue() == EMPTY || cells[i][j]->isOnConflict()) {
              vector<int> availables = getAvailables(Coord(i,j));
              if (availables.size() != 0 && availables.size() < min) {
                min = availables.size();
                hintPos = Coord(i,j);
              }
            } else valueCount[cells[i][j]->getValue()]++;
        }
    }
    // had hintPos
    if (hintPos.isNull()) return false;
    int value;
    vector<int> availables = getAvailables(hintPos);
    vector<int> sortedValues = sort(availables, valueCount);
    if (sortedValues.size() == 0) return false;
    value = sortedValues[0];

    if (inEditMode()) exitEditMode();
    select(hintPos)->mousePressEvent(NULL);
    callClickedValue(value);
    return true;
}

vector<int> UIBoard::getAvailables(Coord position) {
  list<int> idxs = constrains.getConstrains(position);
  vector<int> result;
  bool check[MAX_VALUE];
  for (int i = 0; i < MAX_VALUE; i++) check[i] = true;
  for (list<int>::iterator i = idxs.begin(); i != idxs.end(); i++) {
    Coord csPosition = constrains.getCellPosition(*i);
    int value = select(csPosition)->getValue();
    if (value != EMPTY) check[value] = false;
  }
  for (int i = 1; i <  MAX_VALUE; i++) {
    if (check[i]) result.push_back(i);
  }
  return result;
}

UICell* UIBoard::select(Coord pos) {
    return cells[pos.x][pos.y];
}

void UIBoard::addConstrains(Coord pos) {
  int row = pos.x, column = pos.y;
  for (int i = 0; i < NB_ROWS; i++) {
    if (i != row) {
        constrains.addConstrain(pos, Coord(i, column));
    }
  }
  for (int i = 0; i < NB_COLUMNS; i++) {
    if (i != column) {
        constrains.addConstrain(pos, Coord(row,i));
    }
  }
  for (int i = 0; i < AREA_SQUARE_SIZE; i++) {
    for (int j = 0; j < AREA_SQUARE_SIZE; j++) {
      int areaX = (row/AREA_SQUARE_SIZE) * AREA_SQUARE_SIZE;
      int areaY = (column/AREA_SQUARE_SIZE) * AREA_SQUARE_SIZE;
      if (areaX+i != row || areaY+j != column)
          constrains.addConstrain(pos, Coord(areaX+i, areaY+j));
    }
  }
}

void UIBoard::removeConstrains(Coord pos){
    int row = pos.x, column = pos.y;
    for (int i = 0; i < NB_ROWS; i++) {
      if (i != row) {
          constrains.removeConstrain(pos, Coord(i, column));
      }
    }
    for (int i = 0; i < NB_COLUMNS; i++) {
      if (i != column) {
          constrains.removeConstrain(pos, Coord(row,i));
      }
    }
    for (int i = 0; i < AREA_SQUARE_SIZE; i++) {
      for (int j = 0; j < AREA_SQUARE_SIZE; j++) {
        int areaX = (row/AREA_SQUARE_SIZE) * AREA_SQUARE_SIZE;
        int areaY = (column/AREA_SQUARE_SIZE) * AREA_SQUARE_SIZE;
        if (areaX+i != row || areaY+j != column)
            constrains.removeConstrain(pos, Coord(areaX+i, areaY+j));
      }
    }
}

int UIBoard::random(int n) {
  return rand() % n;
}

void UIBoard::clearLayout(QLayout *layout) {
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

bool UIBoard::checkInputValue(Coord pos, int value) {
    int row = pos.x, column = pos.y;
    for (int i = 0; i < NB_ROWS; i++) {
      if (i != row) {
          if (inputs[i][column] == value) return false;
      }
    }
    for (int i = 0; i < NB_COLUMNS; i++) {
      if (i != column) {
          if (inputs[row][i] == value) return false;
      }
    }
    for (int i = 0; i < AREA_SQUARE_SIZE; i++) {
      for (int j = 0; j < AREA_SQUARE_SIZE; j++) {
        int areaX = (row/AREA_SQUARE_SIZE) * AREA_SQUARE_SIZE;
        int areaY = (column/AREA_SQUARE_SIZE) * AREA_SQUARE_SIZE;
        if (areaX+i != row || areaY+j != column)
            if (inputs[areaX+i][areaY+j] == value) return false;
      }
    }
    return true;
}

void UIBoard::undo() {
    if (!changeHistory.empty()) {
        Changed changed = changeHistory.top();
        changeHistory.pop();
        if (inEditMode()) exitEditMode();
        select(changed.position)->setValue(changed.oldValue);
        repaint();
    }
}

void UIBoard::showDialog() {
    QDialog* dialog = new QDialog;
    QPushButton* newGameBtn = new QPushButton("New game");
    QPushButton* backBtn = new QPushButton("Back");
    QLabel* label = new QLabel;
    QVBoxLayout* layout = new QVBoxLayout;
    QString buttonStyle = "border-radius: 10px;" \
            "background-color: #131d60;" \
            "font-weight: bold;" \
            "color: white";
    QString textStyle = "font-size: 20px; font-weight: bold; color: #131d60;";
    label->setText("Congratulations on completing this Sudoku");
    label->setStyleSheet(textStyle);
    newGameBtn->setStyleSheet(buttonStyle);
    newGameBtn->setFixedSize(160, 40);
    connect(newGameBtn, SIGNAL(clicked()), this, SLOT(newGameBtn_clicked()));
    backBtn->setStyleSheet(buttonStyle);
    backBtn->setFixedSize(160, 40);
    connect(backBtn, SIGNAL(clicked()), this, SLOT(backBtn_clicked()));
    layout->addWidget(label);
    layout->addWidget(newGameBtn);
    layout->addWidget(backBtn);
    layout->setAlignment(label, Qt::AlignHCenter);
    layout->setAlignment(newGameBtn, Qt::AlignHCenter);
    layout->setAlignment(backBtn, Qt::AlignHCenter);
    dialog->setLayout(layout);
    dialog->setFixedSize(500, 200);
    dialog->setStyleSheet("background-color: #b1ebf1;");
    dialog->setWindowTitle("Congratulation");
    dialog->exec();
}

void UIBoard::newGameBtn_clicked() {
    QPushButton* button = qobject_cast<QPushButton *>(sender());
    startNewGame();
    QDialog* dialog = qobject_cast<QDialog *>(sender()->parent());
    dialog->close();
}

void UIBoard::backBtn_clicked() {
    QDialog* dialog = qobject_cast<QDialog *>(sender()->parent());
    dialog->close();
}


void UIBoard::refresh() {
    for (int i = 0; i < NB_ROWS; i++) {
        for (int j = 0; j < NB_COLUMNS; j++) {
            cells[i][j]->refresh();
        }
    }
}
