#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawingview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setLabel(const QString);
    void InitView();
    void setImage(const int& width, const int& height, const uchar *data);
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
