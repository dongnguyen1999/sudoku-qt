    #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void resizeEvent(QResizeEvent*);
    void showSplashScreen();
    void delay(int second);

    ~MainWindow();

private slots:
    void on_btNum1_clicked();

    void on_btNum2_clicked();

    void on_btNum3_clicked();

    void on_btNum4_clicked();

    void on_btNum5_clicked();

    void on_btNum6_clicked();

    void on_btNum7_clicked();

    void on_btNum8_clicked();

    void on_btNum9_clicked();

    void on_btClear_clicked();

    void on_btNewGame_clicked();

    void on_btHint_clicked();

    void on_btUndo_clicked();

    void on_btSolve_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
