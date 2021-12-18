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

void MainWindow::setImage(int width, int height, const uchar *data) {
    int bytes_per_line = width * 4;
    QImage image( data, width, height, bytes_per_line, QImage::Format_ARGB32 );
    this->ui->label->setPixmap(QPixmap::fromImage(image));
}
