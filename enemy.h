#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QMatrix>
#include <QtMath>
#include <QPixmap>
#include <QPainter>
#include <QVector2D>
#include <QRect>
#include <QTimer>
#include "waypoint.h"
#include "function.h"

class Tower;
class GameScene;

class Enemy : public QObject
{
    Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, GameScene *game, const QPixmap &sprite = QPixmap(":/image/enemy_1.png"));
    virtual void draw(QPainter &painter);
    void setHp(int a) { this->current_hp = a;}
    int getHp() { return current_hp;}
    virtual void move();
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
    void getRemoved();
    void getSlow(int i)
    {
        if (run_speed<2)
            run_speed = 5;
        else
            run_speed -= i;
    }

    void getDamage(int damage);
    void slowBuff(int buff) { run_speed -= buff;}
    ~Enemy();
    QPoint pos()const
    {
        return current_pos;
    }
    bool active = false;

protected:
    QPoint current_pos;
    int max_hp = 1500;
    int current_hp = 1500;
    int attack_range = 70;
    int attack = 50;
    int run_speed = 7;
    int level = 1;
    int attack_speed = 1000;
    WayPoint* destination_waypoint;
    QPixmap c_sprite;
    GameScene* m_game;
    QList<Tower*> m_attackedTowersList;
    QTimer* e_fireRateTimer;
    bool arrive_princess = false;

protected slots:
    void setActive();
    void attackCity();

};

class Enemy2 :public Enemy
{
    Q_OBJECT
public:
    Enemy2(WayPoint *startWayPoint, GameScene *game, const QPixmap &sprite = QPixmap(":/image/enemy_2.png"));
    ~Enemy2();
    void move();
};

class Enemy3 :public Enemy
{
    Q_OBJECT
public:
    Enemy3(WayPoint *startWayPoint, GameScene *game, const QPixmap &sprite = QPixmap(":/image/enemy_3.png"));
    ~Enemy3();
    void move();
};

#endif // ENEMY_H
