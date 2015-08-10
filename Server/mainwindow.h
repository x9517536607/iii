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
    MainWindow();
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H