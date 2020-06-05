#include "grid.h"

Grid::Grid(int x, int y, int side):rect(x, y, side, side)
{
    vacant = 1;
}

void Grid::draw(QPainter &painter)
{
    painter.save();
    if (vacant)
        painter.setPen(Qt::white);
    else
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::red);
    }
    painter.drawRect(rect);
    painter.restore();
}
