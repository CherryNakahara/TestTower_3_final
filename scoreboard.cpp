#include "scoreboard.h"

Scoreboard::Scoreboard()
{
}

void Scoreboard::draw(QPainter &painter)
{
    painter.save();
    painter.drawPixmap(1110, 17, money_sprite);
    QFont font("宋体", 30, QFont::Black, true);
    painter.setFont(font);
    const char *k = to_string(money).data();
    //painter.rotate(180);
    painter.drawText(QRect(1110-30*strlen(k),33,200,200), k);
    painter.restore();
}
