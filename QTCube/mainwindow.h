#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QPainter>
#include <QMessageBox>
#include <QImage>
#include <QTimer>
#include <QLabel>
#include <QProgressBar>
#include <cube.h>
#include <setup.h>

//enum {front = 0, rght, back, lft, up, down};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    short side[6][3][3];
    QString comb;
    Cube* solution;
    int step;
    int index;
    QTimer* timer;
    //short arr[3];

    void start();
    QString writeComb();
public slots:
    void getData();
private slots:
    void open_new_window();
    void gotoNextStep();
protected:
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void closeEvent(QCloseEvent* event);
};

#endif // MAINWINDOW_H
