#include "mainwindow.h"
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
    ui->board->build();
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
    ui->centralWidget->setStyleSheet("#centralWidget {border-image: url(:/main/src/assets/images/background.jpg) 0 0 0 0 stretch stretch;background-repeat: no-repeat;}");
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QSize containerSize = ui->boardContainer->size();
    ui->board->resize(QSize(containerSize.height(),containerSize.height()));
    int offset = (containerSize.width()- ui->board->size().width())/2;
    ui->board->move(offset* sqrt(2), 0);
    ui->controlPane->resize(QSize(ui->controlPane->size().width()+offset/2, ui->controlPane->size().height()));
}
