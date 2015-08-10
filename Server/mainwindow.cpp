#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow() :ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //serviceSingleton::getInstance()->addMediaSesstion("rtsp://140.124.182.68:554/live2.sdp", "test");
}
