#include "cube.h"


#define F comb += turn(side, front);
#define R comb += turn(side, rght);
#define B comb += turn(side, back);
#define L comb += turn(side, lft);
#define U comb += turn(side, up);
#define D comb += turn(side, down);
#define F1 comb += turn(side1, front);
#define R1 comb += turn(side1, rght);
#define B1 comb += turn(side1, back);
#define L1 comb += turn(side1, lft);
#define U1 comb += turn(side1, up);
#define D1 comb += turn(side1, down);

#define CHECK_FOR_ERROR if (error)  return "ERROR"

Cube::Cube()
{
    error = false;
    for (int c = front; c <= down; c++)
        for (int j = 0; j < 3; j++)
            for (int i = 0; i < 3; i++)
                unic[c][j][i] = 0;
     short mas[] = {0,1,2,3,4,5,1,2,3,0,4,5,2,3,0,1,4,5,3,0,1,2,4,5,4,1,5,3,2,0,5,1,4,3,0,2};
     short k = 0;
     for (int c = front; c <= down; c++)
         for (int v = front; v <= down; v++) {
              sides[c][v] = mas[k];
                k++;
         }
}

void swap(short& a, short& b)
{
    short z = a;
    a = b;
    b = z;
}


void myswap_front(short front_, short(*arr)[3][3])
{
    short p1, p2, p3;
    p1 = arr[front_][0][0]; p2 = arr[front_][0][1]; p3 = arr[front_][0][2];
    swap(p1, arr[front_][0][2]);
    swap(p2, arr[front_][1][2]);
    swap(p3, arr[front_][2][2]);
    p1 = p3;
    swap(p2, arr[front_][2][1]);
    swap(p3, arr[front_][2][0]);
    p1 = p3;
    swap(p2, arr[front_][1][0]);
    swap(p3, arr[front_][0][0]);
    arr[front_][0][1] = p2;
}


void myswap_near(short front_, short(*arr)[3][3])
{
    short p1, p2, p3;
    if (front_ == front)
    {
        p1 = arr[lft][2][2];	p2 = arr[lft][1][2];	p3 = arr[lft][0][2];
        swap(p1, arr[up][2][0]);
        swap(p2, arr[up][2][1]);
        swap(p3, arr[up][2][2]);
        swap(p1, arr[rght][0][0]);
        swap(p2, arr[rght][1][0]);
        swap(p3, arr[rght][2][0]);
        swap(p1, arr[down][0][2]);
        swap(p2, arr[down][0][1]);
        swap(p3, arr[down][0][0]);
        arr[lft][2][2] = p1;
        arr[lft][1][2] = p2;
        arr[lft][0][2] = p3;
    }
    if (front_ == rght)
    {
        p1 = arr[front][2][2];	p2 = arr[front][1][2];	p3 = arr[front][0][2];
        swap(p1, arr[up][2][2]);
        swap(p2, arr[up][1][2]);
        swap(p3, arr[up][0][2]);
        swap(p1, arr[back][0][0]);
        swap(p2, arr[back][1][0]);
        swap(p3, arr[back][2][0]);
        swap(p1, arr[down][2][2]);
        swap(p2, arr[down][1][2]);
        swap(p3, arr[down][0][2]);
        arr[front][2][2] = p1;
        arr[front][1][2] = p2;
        arr[front][0][2] = p3;
    }
    if (front_ == back)
    {
        p1 = arr[rght][2][2];	p2 = arr[rght][1][2];	p3 = arr[rght][0][2];
        swap(p1, arr[up][0][2]);
        swap(p2, arr[up][0][1]);
        swap(p3, arr[up][0][0]);
        swap(p1, arr[lft][0][0]);
        swap(p2, arr[lft][1][0]);
        swap(p3, arr[lft][2][0]);
        swap(p1, arr[down][2][0]);
        swap(p2, arr[down][2][1]);
        swap(p3, arr[down][2][2]);
        arr[rght][2][2] = p1;
        arr[rght][1][2] = p2;
        arr[rght][0][2] = p3;
    }
    if (front_ == lft)
    {
        p1 = arr[back][2][2];	p2 = arr[back][1][2];	p3 = arr[back][0][2];
        swap(p1, arr[up][0][0]);
        swap(p2, arr[up][1][0]);
        swap(p3, arr[up][2][0]);
        swap(p1, arr[front][0][0]);
        swap(p2, arr[front][1][0]);
        swap(p3, arr[front][2][0]);
        swap(p1, arr[down][0][0]);
        swap(p2, arr[down][1][0]);
        swap(p3, arr[down][2][0]);
        arr[back][2][2] = p1;
        arr[back][1][2] = p2;
        arr[back][0][2] = p3;
    }
    if (front_ == up)
    {
        p1 = arr[lft][0][2];	p2 = arr[lft][0][1];	p3 = arr[lft][0][0];
        swap(p1, arr[back][0][2]);
        swap(p2, arr[back][0][1]);
        swap(p3, arr[back][0][0]);
        swap(p1, arr[rght][0][2]);
        swap(p2, arr[rght][0][1]);
        swap(p3, arr[rght][0][0]);
        swap(p1, arr[front][0][2]);
        swap(p2, arr[front][0][1]);
        swap(p3, arr[front][0][0]);
        arr[lft][0][2] = p1;
        arr[lft][0][1] = p2;
        arr[lft][0][0] = p3;
    }
    if (front_ == down)
    {
        p1 = arr[lft][2][0];	p2 = arr[lft][2][1];	p3 = arr[lft][2][2];
        swap(p1, arr[front][2][0]);
        swap(p2, arr[front][2][1]);
        swap(p3, arr[front][2][2]);
        swap(p1, arr[rght][2][0]);
        swap(p2, arr[rght][2][1]);
        swap(p3, arr[rght][2][2]);
        swap(p1, arr[back][2][0]);
        swap(p2, arr[back][2][1]);
        swap(p3, arr[back][2][2]);
        arr[lft][2][0] = p1;
        arr[lft][2][1] = p2;
        arr[lft][2][2] = p3;
    }

}


void Cube::turn_and_draw(QChar side_rot, short (*side)[3][3])
// принимает сторону поворота и изменяет массив
{
    short myside;
    if (side_rot == 'F')
        myside = front;
    else if (side_rot == 'R')
        myside = rght;
    else if (side_rot == 'B')
        myside = back;
    else if (side_rot == 'L')
        myside = lft;
    else if (side_rot == 'U')
        myside = up;
    else
        myside = down;

    myswap_front(myside, side);
    myswap_near(myside, side);
}


void Cube::setColors(short (*side)[3][3])
{
    for (int c = front; c <= down; c++) {
        for (int j = 0; j < 3; j++)
            for (int i = 0; i < 3; i++)
                col[c][j][i] = side[c][j][i];
        main_clr[c] = col[c][1][1];
    }
    this->setId();
}


void Cube::setId()
// устанавливает уникальные номера для кубиков
{
    // правая и левая грани
    for (int c = rght; c <= lft; c++) {
        for (int j = 0; j < 3; j++)
            unic[c - 1][j][2] = unic[c][j][0] = col[c - 1][j][2] + col[c][j][0];
    }
    for (int j = 0; j < 3; j++)
        unic[lft][j][2] = unic[front][j][0] = col[lft][j][2] + col[front][j][0];

    //up
    unic[up][0][0] = unic[lft][0][0] = unic[back][0][2] += col[up][0][0];	//0 0
    unic[up][0][1] = unic[back][0][1] = col[up][0][1] + col[back][0][1];	//0 1
    unic[up][0][2] = unic[rght][0][2] = unic[back][0][0] += col[up][0][2];	//0 2
    unic[up][1][0] = unic[lft][0][1] = col[up][1][0] + col[lft][0][1];		//1 0
    unic[up][1][2] = unic[rght][0][1] = col[up][1][2] + col[rght][0][1];	//1 2
    unic[up][2][0] = unic[lft][0][2] = unic[front][0][0] += col[up][2][0];	//2 0
    unic[up][2][1] = unic[front][0][1] = col[up][2][1] + col[front][0][1];	//2 1
    unic[up][2][2] = unic[front][0][2] = unic[rght][0][0] += col[up][2][2]; //2 2

    //down
    unic[down][0][0] = unic[lft][2][2] = unic[front][2][0] += col[down][0][0];	// 0 0
    unic[down][0][1] = unic[front][2][1] = col[down][0][1] + col[front][2][1];	// 0 1
    unic[down][0][2] = unic[rght][2][0] = unic[front][2][2] += col[down][0][2];	// 0 2
    unic[down][1][0] = unic[lft][2][1] = col[down][1][0] + col[lft][2][1];		// 1 0
    unic[down][1][2] = unic[rght][2][1] = col[down][1][2] + col[rght][2][1];	// 1 2
    unic[down][2][0] = unic[lft][2][0] = unic[back][2][2] += col[down][2][0];	// 2 0
    unic[down][2][1] = unic[back][2][1] = col[down][2][1] + col[back][2][1];	// 2 1
    unic[down][2][2] = unic[rght][2][2] = unic[back][2][0] += col[down][2][2];	// 2 2

    error = !checkId();
}


bool Cube::checkId()
{
    // устанавливаем ID которые могут существовать
    QSet <short> exist_id;
    exist_id << 0;
    for (short c = front; c <= lft; c++) {
        short next_side = c + 1;
        if (c == lft)
            next_side = front;
        exist_id.insert(main_clr[c] + main_clr[next_side] + main_clr[up]);
        exist_id.insert(main_clr[c] + main_clr[next_side]);
        exist_id.insert(main_clr[c] + main_clr[next_side] + main_clr[down]);
        exist_id.insert(main_clr[c] + main_clr[up]);
        exist_id.insert(main_clr[c] + main_clr[down]);
    }
    for (short c = front; c <= down; c++)
        for (short j = 0; j < 3; j++)
            for (short i = 0; i < 3; i++)
                if ( !(exist_id.contains(unic[c][j][i])))
                     return false;
    return true;
}

short Cube::lookForId(short id_)
// Находит кубик по id и возвращает значения side, y, x
{
    for (int c = front; c <= down; c++)
        for (int j = 0; j < 3; j++)
            for (int i = 0; i < 3; i++)
                if (unic[c][j][i] == id_) {
                    return c;
                }
    return 10;	//ошибка
}


bool Cube::contains(short id_, short cur_side)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            if (unic[cur_side][j][i] == id_)
                return true;
    return false;
}


char Cube::turn(short cur_side, short rot_side)
// cur_side = front* - текущая сторона
// rot_side - сторона поворота относительно cur_side
// возвращает обсолютную сторону поворота
{
    short front_ = sides[cur_side][rot_side];
    myswap_front(front_, col);
    myswap_front(front_, unic);
    myswap_near(front_, col);
    myswap_near(front_, unic);
    switch (front_)
    {
        case front: return 'F';
        case rght: return 'R';
        case back: return 'B';
        case lft: return 'L';
        case up: return 'U';
        case down: return 'D';
    default: return 'E';
    }
    return 'o';
}


QString Cube::getSolution()
// Начало построения решения
{
    CHECK_FOR_ERROR;
    QString comb[7];
    QString answer = "";
                                // Шаг 1: собираем правильны крест на верхней грани
    comb[0] = "";
    for (int c = front; c <= lft; c++)
        comb[0] += step1(c);
    optimization(comb[0]);


                                // Шаг 2: восстанавливаем углы на верхней грани
    comb[1] = "";
    for (int c = front; c <= lft; c++)
        comb[1] += step2(c);
    optimization(comb[1]);

                               // Шаг 3: завершаем среднюю полосу
    comb[2] = "";
    for (int c = front; c <= lft; c++)
        comb[2] += step3(c);
    optimization(comb[2]);

                                // Шаг 4: строим белый крест
    comb[3] = "";
    short side_ = front;
    short clr = main_clr[down];
    while ( !(col[down][0][1] == clr && col[down][1][0] == clr
           && col[down][1][2] == clr && col[down][2][1] == clr))
    {
        comb[3] += step4(side_);
        if (side_ == up) {
            comb[3] += turn(front, back);
            comb[3] += turn(front, down);
            comb[3] += turn(front, rght);
            comb[3] += turn(front, down);
            comb[3] += turn(front, down);
            comb[3] += turn(front, down);
            comb[3] += turn(front, rght);
            comb[3] += turn(front, rght);
            comb[3] += turn(front, rght);
            comb[3] += turn(front, back);
            comb[3] += turn(front, back);
            comb[3] += turn(front, back);
            side_ = front;
        }
        else
            side_++;
    }
    optimization(comb[3]);

                                // Шаг 5: строим правильный белый крест
    comb[4] = "";
    comb[4] += step5(front);
    if (col[front][2][1] != main_clr[front] )
        comb[4] += turn(front, down);
    optimization(comb[4]);

                            // Шаг 6: ставим на место уголки
    comb[5] = "";
    comb[5] += step6(front);
    optimization(comb[5]);

                            // Шаг 7: переворачиваем углы
    comb[6] = "";
    comb[6] += step7(front);
    optimization(comb[6]);

    for (int i = 0; i < 7; i++)
        answer += comb[i];
    // FINAL
    for (int i = 0; i < answer.length() - 3; i++)
        if  ( (answer[i] == answer[i+2] && answer[i+1] == '\'') ||
              (answer[i] == answer[i+1] && answer[i+2] == '\''))
        answer.remove(i, 3);

    return answer;
}

QString Cube::step1(short side)
// сборка правильного верхнего креста и возвращение комбинации
{
    short id_ = main_clr[side] + main_clr[up];
    QString comb = "";
    //writeSideCol(side);
    while (true)
        if (contains(id_, side)) {
            while (!contains(id_, up)) {
                comb += turn(side, front);
            }
        break;
        }
            else if (contains(id_, down)) {
            while (!contains(id_, side))
                comb += turn(side, down);
            }
            else {
                short side1;
                short k(0);
                side1 = lookForId(id_);
                while (!contains(id_, down)) {
                    comb += turn(side1, front);
                    k++;
                }
            comb += turn(side1, down);
            // возвращаем обратно против часовой стрелки
            for (int i = 0; i < k*3; i++)
                comb += turn(side1, front);		// == 1 раз против часовой
            }

    // на своем месте
    if (col[side][0][1] == main_clr[side])
    return comb;
    // FU'RU
    comb += turn(side, front);
    comb += turn(side, up);		comb += turn(side, up);		comb += turn(side, up);	// == 1 раз против часовой
    comb += turn(side, rght);
    comb += turn(side, up);
    return comb;
}


QString Cube::step2(short side)
{
    short next_side;
    if (side == lft)
        next_side = front;
    else
        next_side = side + 1;

    short id_ = main_clr[side] + main_clr[up] + main_clr[next_side];

    QString comb = "";
    while (true)
        if (contains(id_, side) && contains(id_, next_side))
            break;
        else if (contains(id_, down))
        {
            while (!contains(id_, side) || !contains(id_, next_side))
                comb += turn(side, down);
        }
        else
        {
            short side1;
            side1 = lookForId(id_);
            if (unic[up][2][0] == id_)
                side1 = lft;
            while (!contains(id_, down)) {
                // R'D'RD
                comb += turn(side1, rght);	comb += turn(side1, rght);	comb += turn(side1, rght);
                comb += turn(side1, down);	comb += turn(side1, down);	comb += turn(side1, down);
                comb += turn(side1, rght);
                comb += turn(side1, down);
            }
        }

    // на своем месте
    while (col[side][0][2] != main_clr[side] || col[next_side][0][0] != main_clr[next_side])
    {
        // R'D'RD
        comb += turn(side, rght);	comb += turn(side, rght);	comb += turn(side, rght);
        comb += turn(side, down);	comb += turn(side, down);	comb += turn(side, down);
        comb += turn(side, rght);
        comb += turn(side, down);
    }
    return comb;
}


QString Cube::step3(short side)
{
    short next_side;
    if (side == lft)
        next_side = front;
    else
        next_side = side + 1;

    short id_ = main_clr[side] + main_clr[next_side];
    QString comb = "";
    while (true)
        if (contains(id_, side) && contains(id_, next_side))
            if (col[side][1][2] == main_clr[side])
                break;
            else
            {
                // D'R'DR	DFD'F'
                D D D R R R D R
                D F D D D F F F
            }
        else if (contains(id_, down)) {
            while ( !(unic[side][2][1] == id_))
                D
            if (col[side][2][1] == main_clr[side]) {
                    // D'R'DR	DFD'F'
                    D D D R R R D R
                    D F D D D F F F
            }
            else
            {
                short side1 = next_side;
                D
                D1 L1 D1 D1 D1 L1 L1 L1
                D1 D1 D1 F1 F1 F1 D1 F1
            }
        }
        else
        {
            short side1 = lookForId(id_);
            if (contains(id_, lft) && contains(id_, front))
                side1 = lft;
            // D'R'DR	DFD'F'
            D1 D1 D1 R1 R1 R1 D1 R1
            D1 F1 D1 D1 D1 F1 F1 F1
        }
    return comb;
}

// !!!!!!!!!
QString Cube::step4(short side)
{
    QString comb = "";
    short clr = main_clr[down];
    if (side == front && col[down][1][0] == clr) {
        if (col[down][0][1] == clr) {
            B D R D D D
            R R R B B B
        }
        else if (col[down][1][2] == clr) {
            B R D R R R
            D D D B B B
        }
    }
    if (side == rght && col[down][2][1] == clr) {
        if (col[down][1][0] == clr) {
            B D R D D D
            R R R B B B
        }
        else if (col[down][0][1] == clr) {
            B R D R R R
            D D D B B B
        }
    }
    if (side == back && col[down][1][2] == clr) {
        if (col[down][2][1] == clr) {
            B D R D D D
            R R R B B B
        }
        else if (col[down][1][0] == clr) {
            B R D R R R
            D D D B B B
        }
    }
    if (side == lft && col[down][0][1] == clr) {
        if (col[down][1][2] == clr) {
            B D R D D D
            R R R B B B
        }
        else if (col[down][2][1] == clr) {
            B R D R R R
            D D D B B B
        }
    }
    return comb;
}


QString Cube::step5(short side)
{
    short next_side = side + 1;
    if (side == lft)
        next_side = front;

    QString comb = "";

    short k = 0;
    for (int c = front; c <= lft; c++)
        if (col[c][2][1] == main_clr[c])
            k++;

    if (k == 4)
        return comb;

    if (col[side][2][1] == main_clr[side] && col[next_side][2][1] == main_clr[next_side])
    {
        R D R R R D R D D R R R		// *
            return comb;
    }
    else if ( side != back && (col[side][2][1] == main_clr[side] && col[next_side + 1][2][1] == main_clr[next_side + 1]))
    {
        L D L L L D L D D L L L
        comb += step5(side);
    }
    else {
        if (side == lft)
            D
            comb += step5(next_side);
    }
    return comb;
}


QString Cube::step6(short side)
{
    QString comb = "";
    short next_side = side + 1;
    if (side == lft)
        next_side = front;

    short next2_side = side + 2;
    if (side == back)
        next2_side = front;
    if (side == lft)
        next2_side = rght;

    if (!check(front) && !check(rght) && !check(back) && !check(lft)) {
        D L D D D R R R D L L L D D D R
    }
    if (check(side))
    {
        if (check(next_side))
            return comb;
        if (unic[side][2][0] == main_clr[next_side] + main_clr[next2_side] + main_clr[down]) {	// по час
            D D D R R R D L D D D R D L L L
        }
        else {			// против час
            D F D D D B B B D F F F D D D B
        }
    }
    else
        comb += step6(next_side);
    return comb;
}

bool Cube::check(short side)
{
    short next_side = side + 1;
    if (side == lft)
        next_side = front;

    if (unic[side][2][2] == main_clr[side] + main_clr[next_side] + main_clr[down])
        return true;
    return false;
}

QString Cube::step7(short side)
{
    QString comb = "";
    for (int c = front; c <= lft; c++)
    {
        while ( !(col[front][2][0] == col[front][2][1] && col[lft][2][2] == col[lft][2][1])) {
            L L L U U U L U
        }
        D
    }
    return comb;
}


void Cube::optimization(QString& comb)
{
    int k = 0;
    QString str = "";
    int i = 0;
    int len = comb.length();
    while (i < len)
    {
        k = i + 1;
        while (k < len && comb[i] == comb[k])
            k++;
        if (k - i > 1) {
            QChar x = comb[i];
            int ost = (k - i) % 4;
            switch (ost) {
            case 3: {	str = str + x + "\'"; break; }
            case 2: {	str = str + x + x; break; }
            case 1: {	str = str + x;	break; }
            default:
                break;
            }
        }
        else
            str = str + comb[i];
        i = k;
    }
    comb = str;
}

Cube::~Cube()
{
}
