#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLabel(const QString str) {
    this->ui->label->setText(str);
}

void MainWindow::InitView() {

}

void MainWindow::setImage(const int& width, const int& height, const uchar *data) {
    int bytes_per_line = width * 3;
    QImage image( data, width, height, bytes_per_line, QImage::Format_RGB888 );
    this->ui->label->setPixmap(QPixmap::fromImage(image));
}
