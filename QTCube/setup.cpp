#include "setup.h"
#include "ui_setup.h"

#include <QDebug>


enum {front = 0, rght, back, lft, up, down};
enum {blue = 1, red = 2, green = 4, orange = 8, yellow = 15, white = 28};

setup::setup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setup)
{
    ui->setupUi(this);
    setFixedSize(560, 290);
    QGridLayout *lay[6];
    QList <QString> list = {"blue", "red", "green", "orange", "yellow", "white" };
    for (short c = front; c <= down; c++)
    {
        lay[c] = new QGridLayout(this);
        QWidget *cur_tab;
        switch (c) {
        case front: { cur_tab = ui->tab_front; break; }
        case rght: { cur_tab = ui->tab_right; break; }
        case back: { cur_tab = ui->tab_back; break; }
        case lft: { cur_tab = ui->tab_left; break; }
        case up: { cur_tab = ui->tab_up; break; }
        case down: { cur_tab = ui->tab_down; break; }
        }
        cur_tab->setLayout(lay[c]);
        for (short j = 0; j < 3; j++)
            for (short i = 0; i < 3; i++)
            {
                choise_color[c][j][i] = new QComboBox(cur_tab);
                QComboBox* cur_choise = choise_color[c][j][i];
                cur_choise->setLayout(lay[c]);
                cur_choise->setGeometry(i*65 + 40, j*65 + 30, 60, 60);
                cur_choise->addItems(list);
                connect(cur_choise, SIGNAL(currentIndexChanged(int)), this, SLOT(changeColor(int)));
            }
        list.append(list.first());
        list.removeFirst();
    }
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(changeTab()));
    connect(ui->but_cancel, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->but_ok, SIGNAL(clicked(bool)), this, SLOT(okClicked()));
}


short next_col(short cur_side, QString &text)
{
    if (cur_side == blue) {
        text = "red";
        return red;
    }
    if (cur_side == red) {
        text = "green";
        return green;
    }
    if (cur_side == green) {
        text = "orange";
        return orange;
    }
    if (cur_side == orange) {
        text = "yellow";
        return yellow;
    }
    if (cur_side == yellow) {
        text = "white";
        return white;
    }
    text = "blue";
    return blue;
}


void setup::changeTab()
{
    repaint();
}

void setup::changeColor(int a)
{
    Q_UNUSED(a);
    int cur_side = ui->tabWidget->currentIndex();
    QObject *cur_choise = QObject::sender();
    int j0, i0;
    QString item_text;
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            if (cur_choise == choise_color[cur_side][j][i]) {
               j0 = j;
               i0 = i;
               item_text = choise_color[cur_side][j][i]->currentText();
               break;
            }
    if (item_text == "blue")
        side[cur_side][j0][i0] = 1;
    else if (item_text == "red")
        side[cur_side][j0][i0] = 2;
    else if (item_text == "green")
        side[cur_side][j0][i0] = 4;
    else if (item_text == "orange")
        side[cur_side][j0][i0] = 8;
    else if (item_text == "yellow")
        side[cur_side][j0][i0] = 15;
    else if (item_text == "white")
        side[cur_side][j0][i0] = 28;
    repaint();
}

void setup::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    if (x > 25 && x <250 &&
            y > 30 && y < 255 )
    {
        int cur_side = ui->tabWidget->currentIndex();
        x -= 25;    y -= 30;
        int i = x / 75;
        int j = y / 75;
        QString text_item;
        side[cur_side][j][i] = next_col(side[cur_side][j][i], text_item);
        choise_color[cur_side][j][i]->setCurrentText(text_item);
        repaint();
    }
}



void setup::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter paint(this);
    int cur_side = ui->tabWidget->currentIndex();
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
        {
            short col = side[cur_side][j][i];
            switch (col) {
                case 1: { paint.setBrush(QColor::fromRgb(38, 144, 255));; break; }
                case 2: { paint.setBrush(QColor::fromRgb(254, 40, 162)); break; }
                case 4: { paint.setBrush(Qt::green); break; }
                case 8: { paint.setBrush(QColor::fromRgb(250, 117, 24)); break; }
                case 15: {paint.setBrush(Qt::yellow); break; }
                case 28: {paint.setBrush(Qt::white); break; }
            }
            paint.setPen(Qt::black);
            paint.drawRect(i * 75 + 25, 30 + j * 75, 75, 75);
        }
}

void setup::setOriginalSide(short (*arr)[3][3])
// принимает исходныные данные от главного окна
{
    original_side = arr;
    for (int c = front; c <= down; c++)
        for (int j = 0; j < 3; j++)
            for (int i = 0; i < 3; i++)
                side[c][j][i] = arr[c][j][i];
}


void setup::okClicked()
{
    // сохраняем введные данные в оригинал
    for (int c = front; c <= down; c++)
        for (int j = 0; j < 3; j++)
            for (int i = 0; i < 3; i++)
                original_side[c][j][i] = side[c][j][i];
    this->close();
    emit sendData();
}

setup::~setup()
{
    delete ui;
}
