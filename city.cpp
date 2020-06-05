#include "city.h"

City::City(const QPixmap &sprite):pos(970,370),c_sprite(sprite)
{

}

void City::draw(QPainter &painter)
{
    painter.save();
    static const int Health_Bar_Width = 130;
    QPoint healthBarPoint =  QPoint(pos.x()-Health_Bar_Width/2+30, pos.y()-50);
    // 绘制血条
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 5));
    painter.drawRect(healthBarBackRect);
    if (current_hp>0)
    {
        painter.setBrush(Qt::green);
        QRect healthBarRect(healthBarPoint, QSize(current_hp/(double)max_hp * Health_Bar_Width, 5));
        painter.drawRect(healthBarRect);
    }
    painter.translate(pos);
    painter.restore();
}

bool City::getDie()
{
    if (current_hp > 0)
        return false;
    else
        return true;
}
