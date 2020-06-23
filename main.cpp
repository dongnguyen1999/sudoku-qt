#include "src/widgets/mainwindow.h"
#include <QApplication>
#include<QThread>
#include<QTime>
#include<QGridLayout>
#include<QFrame>
#include<QWidget>
#include<QPushButton>
#include<QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    w.showSplashScreen();
    return a.exec();
}
