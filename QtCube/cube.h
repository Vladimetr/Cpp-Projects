#ifndef CUBE_H
#define CUBE_H

#include <QString>
#include <QSet>

enum {front = 0, rght, back, lft, up, down};
enum {blue = 1, red = 2, green = 4, orange = 8, yellow = 15, white = 28};

class Cube
{
public:
    Cube();
    void setColors(short (*side)[3][3]); // установка цветов
    QString getSolution();
    void turn_and_draw(QChar side_rot, short (*side)[3][3]);         // for MainWindow
    virtual ~Cube();
private:
        bool error;
        short col[6][3][3];
        short col_begin[6][3][3];
        short main_clr[6];
        short unic[6][3][3];
        short sides[6][6];	// относительность каждой стороны
        void setId();	// установка уникальных номеров каждого кубика
        bool checkId();
        short lookForId(short id_);
        bool contains(short id_, short side);		// содержит ли сторона данный кубик
        char turn(short cur_side, short rot_side);	// функция поворота

        QString step1(short side);
        QString step2(short side);
        QString step3(short side);
        QString step4(short side);
        QString step5(short side);
        QString step6(short side);
        bool check(short side);
        QString step7(short side);
        void optimization(QString& comb);
};

#endif // CUBE_H
