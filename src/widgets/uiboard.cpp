#include "src/widgets/uiboard.h"
#include <QDebug>
#include <QGridLayout>
#include <QStyleOption>
#include <QPainter>

UIBoard::UIBoard(QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout;
    layout->setMargin(8);
    layout->setHorizontalSpacing(4);
    layout->setVerticalSpacing(4);
    setLayout(layout);
}

void UIBoard::paintEvent(QPaintEvent *) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void UIBoard::syncBoard() {
    for (int i = 0; i < NB_ROWS; i++) {
        for (int j = 0; j < NB_COLUMNS; j++) {
            cells[i][j] = new UICell(board.select(Coord(i,j)), this);
        }
    }
}

void UIBoard::build() {
    syncBoard();
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

void UIBoard::highLightRCA(Cell cell, bool willHover) {
    Coord position = cell.getPosition();
    int row = position.x, column = position.y;
    for (int i = 0; i < NB_COLUMNS; i++) {
        cells[row][i]->highLight(willHover);
    }
    for (int i = 0; i < NB_ROWS; i++) {
        cells[i][column]->highLight(willHover);
    }
    int xArea = row/AREA_SQUARE_SIZE, yArea = column/AREA_SQUARE_SIZE;
    for (int i = 0; i < AREA_SQUARE_SIZE; i++) {
        for (int j = 0; j < AREA_SQUARE_SIZE; j++) {
            cells[AREA_SQUARE_SIZE*xArea+i][AREA_SQUARE_SIZE*yArea+j]->highLight(willHover);
        }
    }
}

void UIBoard::turnToEditMode(Cell cell) {
    onEditing = true;
    editingCell = cell;
    highLightRCA(cell, true);
}

bool UIBoard::inEditMode() {
    return onEditing;
}

void UIBoard::exitEditMode() {
    if (inEditMode()) {
        onEditing = false;
        Coord pos = editingCell.getPosition();
        cells[pos.x][pos.y]->exitEditMode();
        cells[pos.x][pos.y]->setHover(false);
        highLightRCA(editingCell, false);
    }
}

