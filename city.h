#ifndef CITY_H
#define CITY_H

#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QList>
#include <QSize>
#include <string>
#include "enemy.h"

class GameScene;

class City
{
public:
    City(const QPixmap &sprite = QPixmap(":/image/city.png"));
    void setGame(GameScene * game) { m_game = game;}
    ~City() {}
    void draw(QPainter &painter);
    void getDamage(int damage) { current_hp -= damage;}
    bool getDie();
    QList <Enemy *> enemy_list;
    int current_hp = 2000;

private:
    QList <QPixmap *> sprite_list;
    GameScene * m_game;
    QPoint pos;
    QPixmap c_sprite;
    int max_hp = 2000;
};

#endif // CITY_H
