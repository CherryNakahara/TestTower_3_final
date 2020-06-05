#include "bullet.h"
#include "enemy.h"
#include "gamescene.h"
#include <QPainter>
#include <QPropertyAnimation>

const QSize Bullet::ms_fixedSize(20, 20);

Bullet::Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
               GameScene *game, const QPixmap &sprite)
    : m_startPos(startPos)
    , m_targetPos(targetPoint)
    , m_sprite(sprite)
    , m_currentPos(startPos)
    , m_target(target)
    , m_game(game)
    , m_damage(damage)
{
}

void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(m_currentPos, m_sprite);
}

void Bullet::move()
{
    // 100毫秒内击中敌人
    static const int duration = 100;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));

    animation->start();
}

void Bullet::move2()
{
    // 100毫秒内击中敌人
    static const int duration = 100;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(slowTarget()));

    animation->start();
}

void Bullet::move3()
{
    // 100毫秒内击中敌人
    static const int duration = 100;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(fastTarget()));

    animation->start();
}

void Bullet::hitTarget()
{
    // 这样处理的原因是:
    // 可能多个炮弹击中敌人,而其中一个将其消灭,导致敌人delete
    // 后续炮弹再攻击到的敌人就是无效内存区域
    // 因此先判断下敌人是否还有效
    if (m_game->m_enemylist().indexOf(m_target) != -1)
    {
        m_target->getDamage(m_damage);
        m_game->removedBullet(this);
    }
}


void Bullet::slowTarget()
{
    if (m_game->m_enemylist().indexOf(m_target) != -1)
    {
        m_target->getDamage(m_damage);
        m_target->getSlow(2);
        m_game->removedBullet(this);
    }
}

void Bullet::fastTarget()
{
    if (m_game->m_enemylist().indexOf(m_target) != -1)
    {
        m_target->getDamage(m_damage);
        m_target->getSlow(-1);
        m_game->removedBullet(this);
    }
}

void Bullet::setCurrentPos(QPoint pos)
{
    m_currentPos = pos;
}

QPoint Bullet::currentPos() const
{
    return m_currentPos;
}
