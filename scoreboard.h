#ifndef SCOREBOARD_H
#define SCOREBOARD_H


#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QFont>
#include <string>

using namespace std;


class Scoreboard
{
public:
    Scoreboard();
    void setMoney(int i) { money += i;}
    virtual void draw(QPainter &painter);
    int getMoney() { return money;}

private:
    QPixmap money_sprite = QPixmap(":/image/money.png");
    int money = 400;

};

#endif // SCOREBOARD_H
