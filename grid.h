#ifndef GRID_H
#define GRID_H

#include <QRect>
#include <QPainter>
#include <QPoint>


class Grid
{
public:
    Grid(int x, int y, int side);
    QRect getRect() { return rect;}
    void draw(QPainter &painter);
    bool getVacant() { return vacant;}
    void setVacant() { vacant = 0;}
    int number;

private:
    bool vacant;
    QRect rect;
};

#endif // GRID_H
