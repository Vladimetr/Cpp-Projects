#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1000, 620);
    QFont font("Times", 24);
    ui->lab_step->setFont(font);
    ui->lab_step->setStyleSheet(QString("color: green"));
    ui->lab_step->setAlignment(Qt::AlignRight);
    ui->lab_steps->setFont(font);
    ui->lab_steps->setStyleSheet(QString("color: green"));
    ui->lab_steps->setAlignment(Qt::AlignLeft);
    font.setPixelSize(72);
    ui->lab_comb->setFont(font);
    ui->lab_comb->setStyleSheet(QString("color: red"));
    font.setPixelSize(50);
    ui->lab_comb_before->setFont(font);
    ui->lab_comb_before->setStyleSheet(QString("color: grey"));
    ui->lab_comb_next->setFont(font);
    ui->lab_comb_next->setStyleSheet(QString("color: grey"));
    QImage icon_back(":/resourses/images/back.png");
    ui->icon_back->setPixmap(QPixmap::fromImage(icon_back));
    QImage icon_next(":/resourses/images/next.png");
    ui->icon_next->setPixmap(QPixmap::fromImage(icon_next));
    solution = NULL;
    comb = "";
    for (short c = front; c <= down; c++)
        for (short j = 0; j < 3; j++)
            for (short i = 0; i < 3; i++)
                switch (c) {
                case front: { side[c][j][i] = 1; break; }
                case rght: { side[c][j][i] = 2; break; }
                case back: { side[c][j][i] = 4; break; }
                case lft: { side[c][j][i] = 8; break; }
                case up: { side[c][j][i] = 15; break; }
                case down: { side[c][j][i] = 28; break; }
                }
    connect(ui->but_setup, SIGNAL(clicked()), this, SLOT(open_new_window()));
    repaint();
}


void MainWindow::open_new_window()
{
    setup* new_window = new setup(this);
    new_window->setOriginalSide(side);
    connect(new_window, SIGNAL(sendData()), this, SLOT(getData()));
    new_window->show();
}


void MainWindow::start()
{
    if (solution != NULL)
        delete solution;
    solution = new Cube();
    solution->setColors(side);
    comb = solution->getSolution();
    if (comb == "ERROR") {
        QMessageBox::critical(this,"Ошибка", "Вы неверно ввели цвета кубика. Пожалуйста, задайте цвета заново");
        return;
    }
    short steps = 0;
    for (int i = 0; i < comb.length(); i++)
        if (comb[i] != '\'')
            steps++;
    QString str;
    str.setNum(steps);
    ui->lab_steps->setText("/" + str);
    str = "Алгоритм создан. Кубик можно собрать за " + str + " шага(ов)" ;
    QMessageBox::information(this,"Информация", str);
    comb = ">" + comb;
    index = 0;
    step = 0;
    ui->lab_comb_before->setText("");
    ui->lab_comb->setText("");
    ui->lab_comb_next->setText("");
    writeComb();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(gotoNextStep()));
    repaint();
}

QString MainWindow::writeComb()
// устанавливает label'ы
// и возвращает текущий поворот
{
    QString str;
    str.setNum(step);
    ui->lab_step->setText(str);
    QString str_before = "";
    short i = index;
    short k = 0;
    while ( i > 0 && k < 3) {
        i--;
        str_before = comb[i] + str_before;
        if (comb[i] != '\'')
            k++;
    }
    str = "" + comb[index];
    i = index + 1;
    k = 0;
    if (comb[i] == '\'') {
        str += '\'';
        i++;
    }
    QString str_next = "";
    while (i < comb.length() && k < 3) {
        str_next = str_next + comb[i];
        if (comb[i] != '\'')
            k++;
        i++;
    }

    ui->lab_comb_before->setText(str_before);
    ui->lab_comb->setText(str);
    ui->lab_comb_next->setText(str_next);
    return str;
}

void MainWindow::getData()
// Цвета заданы пользователем
{
    this->start();
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter paint(this);
    for (short c = front; c <= down; c++)
        for (short j = 0; j < 3; j++)
            for (short i = 0; i < 3; i++)
            {
                short col = side[c][j][i];
                switch (col) {
                    case 1: { paint.setBrush(QColor::fromRgb(38, 144, 255));; break; }
                    case 2: { paint.setBrush(QColor::fromRgb(254, 40, 162)); break; }
                    case 4: { paint.setBrush(Qt::green); break; }
                    case 8: { paint.setBrush(QColor::fromRgb(250, 117, 24)); break; }
                    case 15: {paint.setBrush(Qt::yellow); break; }
                    case 28: {paint.setBrush(Qt::white); break; }
                }
                paint.setPen(Qt::black);
                paint.drawRect(c*160 + i * 40 + 40, 440 + j * 40, 40, 40);
            }
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
if ( int(event->key()) == 1070) // >
{
    gotoNextStep();
}

if (int(event->key()) == 1041 && comb != "")    // <
  if (index > 0)
   {
        step--;
        index--;
        QString side_rot = ui->lab_comb->text();

        if (side_rot.length() == 1) {
            solution->turn_and_draw(side_rot[0], side);
            solution->turn_and_draw(side_rot[0], side);
            solution->turn_and_draw(side_rot[0], side);
        }
        else
            solution->turn_and_draw(side_rot[0], side);

        if (comb[index] == '\'')
            index--;

        side_rot = writeComb();
        repaint();
    }
}


void MainWindow::gotoNextStep()
{
timer->stop();
if (QObject::sender() == timer && !(ui->checkBox->isChecked()))
    return;
if (index+1 < comb.length())
 {
            step++;
            index++;
            if ( comb[index] == '\'')
                index++;
            QString side_rot = writeComb();
            if (side_rot.length() == 1)                          // по часовой
                 solution->turn_and_draw(side_rot[0], side);
            else {                                               // против часовой
                 solution->turn_and_draw(side_rot[0], side);
                 solution->turn_and_draw(side_rot[0], side);
                 solution->turn_and_draw(side_rot[0], side);
            }
            repaint();
   if (ui->checkBox->isChecked()) {
     int sec = ui->spinBox->value();
     timer->start(sec * 1000);
 }
}
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton answer = QMessageBox::question(this,"Выход", "Закрыть приложение?", QMessageBox::Yes | QMessageBox::No );
    if (answer == QMessageBox::Yes)
            event->accept();
        else
            event->ignore();
}

MainWindow::~MainWindow()
{
    if (solution != NULL)
        delete solution;
    delete ui;

}
