#include "src/widgets/mainwindow.h"
#include "ui_mainwindow.h"
#include "src/widgets/uicell.h"
#include<QDebug>
#include<QPainter>
#include<QPixmap>
#include<math.h>
#include<QTime>
#include<QGridLayout>
#include<QFrame>
#include<QWidget>
#include<QPushButton>
#include<QLabel>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Sudoku QT");
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::delay(int second)
{
    QTime dieTime = QTime::currentTime().addSecs(second);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::showSplashScreen() {
    ui->boardContainer->setHidden(true);
    ui->controlPane->setHidden(true);
    delay(2);
    ui->boardContainer->setHidden(false);
    ui->controlPane->setHidden(false);
    ui->centralWidget->setStyleSheet("border-image: url(:/main/src/assets/images/background.jpg) 0 0 0 0 stretch stretch;background-repeat: no-repeat;");
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QSize containerSize = ui->boardContainer->size();
    ui->board->resize(QSize(containerSize.height(),containerSize.height()));
    int offset = (containerSize.width()- ui->board->size().width())/2;
    ui->board->move(offset* sqrt(2), 0);
    ui->controlPane->resize(QSize(ui->controlPane->size().width()+offset/2, ui->controlPane->size().height()));
//    ui->board->refresh();
}

void MainWindow::on_btNum1_clicked()
{
    ui->board->callClickedValue(1);
}

void MainWindow::on_btNum2_clicked()
{
    ui->board->callClickedValue(2);
}

void MainWindow::on_btNum3_clicked()
{
    ui->board->callClickedValue(3);
}

void MainWindow::on_btNum4_clicked()
{
    ui->board->callClickedValue(4);
}

void MainWindow::on_btNum5_clicked()
{
    ui->board->callClickedValue(5);
}

void MainWindow::on_btNum6_clicked()
{
    ui->board->callClickedValue(6);
}

void MainWindow::on_btNum7_clicked()
{
    ui->board->callClickedValue(7);
}

void MainWindow::on_btNum8_clicked()
{
    ui->board->callClickedValue(8);
}

void MainWindow::on_btNum9_clicked()
{
    ui->board->callClickedValue(9);
}

void MainWindow::on_btClear_clicked()
{
    ui->board->callClickedValue(0);
}

void MainWindow::on_btNewGame_clicked()
{
    ui->board->startNewGame();
}

void MainWindow::on_btHint_clicked()
{
    ui->board->hint();
}

void MainWindow::on_btUndo_clicked()
{
    ui->board->undo();
}
