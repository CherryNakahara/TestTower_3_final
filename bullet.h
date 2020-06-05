#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class QPainter;
class Enemy;
class GameScene;

class Bullet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)
public:
    Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
           GameScene *game, const QPixmap &sprite = QPixmap(":/image/bullet.png"));

    void draw(QPainter *painter) const;
    void move();
    void move2();
    void move3();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;

private slots:
    void hitTarget();
    void slowTarget();
    void fastTarget();

private:
    const QPoint	m_startPos;
    const QPoint	m_targetPos;
    const QPixmap	m_sprite;
    QPoint			m_currentPos;
    Enemy *	m_target;
    GameScene *	m_game;
    int				m_damage;

    static const QSize ms_fixedSize;

};

#endif // BULLET_H
