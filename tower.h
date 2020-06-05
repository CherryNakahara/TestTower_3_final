#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include "bullet.h"
#include "function.h"
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>
#include "enemy.h"
#include "gamescene.h"

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos, GameScene* game, const QPixmap &sprite = QPixmap(":/image/tower.png"), const QPixmap &b_sprite = QPixmap(":/image/buff.png"));
    virtual void draw(QPainter &painter);
    ~Tower(){}
    virtual void attackEnemy();
    void chooseEnemyForAttack(Enemy *enemy);
    void targetKilled();
    void checkEnemyInRange();
    void lostSightOfEnemy();
    void upLevel();
    void addSpeed(int speed) { attack_speed+=speed;}
    Enemy* m_chooseEnemy=NULL;
    QPoint pos;
    bool circle = true;

protected:
    int attack_range = 200;
    QPixmap t_sprite;
    QPixmap buff_sprite;
    QTimer* m_fireRateTimer;
    int attack = 50;
    int attack_speed = 300;
    int level = 1;
    GameScene* m_game;
    double m_rotationSprite = 0.0;

private:
    virtual void shootWeapon();

};

class Firetower: public Tower
{
    Q_OBJECT
public:
    Firetower(QPoint pos, GameScene* game, const QPixmap &sprite = QPixmap(":/image/fire.png"), const QPixmap &b_sprite = QPixmap(":/image/buff.png"));
    ~Firetower(){}
    virtual void draw(QPainter &painter);
    void attackEnemy();

private:
    int attack_range = 200;
    int attack = 300;
    int attack_speed = 600;

private slots:
    void shootWeapon();

};

class Icetower: public Tower
{
    Q_OBJECT
public:
    Icetower(QPoint pos, GameScene* game, const QPixmap &sprite = QPixmap(":/image/ice.png"), const QPixmap &b_sprite = QPixmap(":/image/buff.png"));
    ~Icetower(){}
    virtual void draw(QPainter &painter);
    void attackEnemy();

private:
    int attack_range = 200;
    int attack = 100;
    int attack_speed = 600;

private slots:
    void shootWeapon();
};

#endif // TOWER_H
