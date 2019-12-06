#ifndef SETUP_H
#define SETUP_H

#include <QDialog>
#include <QGridLayout>
#include <QTabWidget>
#include <QComboBox>
#include <QPainter>
#include <QMouseEvent>
#include <QList>


//enum {front = 0, rght, back, lft, up, down};

namespace Ui {
class setup;
}

class setup : public QDialog
{
    Q_OBJECT

public:
    explicit setup(QWidget *parent = 0);
    ~setup();
    void setOriginalSide(short (*arr)[3][3]);
private:
    Ui::setup *ui;
    short side[6][3][3];
    short (*original_side)[3][3];           // указатель на оригинал
    QGridLayout *lay[6];
    QComboBox *choise_color[6][3][3];

private slots:
    void changeTab();
    void changeColor(int a);
    void okClicked();
signals:
    void sendData();
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
};

#endif // SETUP_H
