#include "tower.h"

Tower::Tower(QPoint pos, GameScene* game, const QPixmap &sprite, const QPixmap &b_sprite)
    :pos(pos) , t_sprite(sprite) , buff_sprite(b_sprite), m_game(game)
{
    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

void Tower::draw(QPainter &painter)//需要传递painter画笔
{
    painter.save();
    // 绘制塔
    painter.translate(pos); // 将pos设置成原点
    if (level==2)
        painter.drawPixmap(-100, -60, buff_sprite);
    painter.drawPixmap(-50, -50, 100, 100, t_sprite); //在（-50，-50）画图象
    painter.restore();
}

void Tower::attackEnemy()
{	// 启动打炮模式
    m_fireRateTimer->start(attack_speed);
}

void Tower::chooseEnemyForAttack(Enemy *enemy)
{	// 选择敌人,同时设置对敌人开火
    m_chooseEnemy = enemy;	// 这里启动timer,开始打炮
    attackEnemy();	// 敌人自己要关联一个攻击者,这个用QList管理攻击者,因为可能有多个
    m_chooseEnemy->getAttacked(this);
}

void Tower::shootWeapon()
{	// 每次攻击,产生一个子弹
    // 子弹一旦产生,交由m_game管理,进行绘制
    Bullet *bullet = new Bullet(pos, m_chooseEnemy->pos(), attack, m_chooseEnemy, m_game);
    bullet->move();
    m_game->addBullet(bullet);
}

void Tower::targetKilled()
{	// 目标死亡时,也需要取消关联
    // 取消攻击
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;
    m_fireRateTimer->stop();
    m_rotationSprite = 0.0;
}

void Tower::lostSightOfEnemy()
{	// 当敌人脱离炮塔攻击范围,要将炮塔攻击的敌人关联取消
    // 同时取消攻击
    m_chooseEnemy->gotLostSight(this);
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;
    m_fireRateTimer->stop();
    m_rotationSprite = 0.0;
}

void Tower::checkEnemyInRange()
{
    if (m_chooseEnemy)
    {
        // 这种情况下,需要旋转炮台对准敌人
        // 向量标准化
        QVector2D normalized(m_chooseEnemy->pos() - pos);
        normalized.normalize();
        m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;

        // 如果敌人脱离攻击范围
        if (!arrive(pos, attack_range, m_chooseEnemy->pos(), 1))
            lostSightOfEnemy();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        QList<Enemy *> enemyList = m_game->m_enemylist();
        foreach (Enemy *enemy, enemyList)
        {
            if (arrive(pos, attack_range, enemy->pos(), 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}

void Tower::upLevel()
{
    level = 2;
    attack += 50;
    attack_speed += 100;
}

Firetower::Firetower(QPoint pos, GameScene* game, const QPixmap &sprite, const QPixmap &b_sprite)
    :Tower(pos, game, sprite, b_sprite)
{
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
    buff_sprite = QPixmap(":/image/buff.png");
}

void Firetower::draw(QPainter &painter)//需要传递painter画笔
{
    painter.save();
    // 绘制塔
    painter.translate(pos); // 将pos设置成原点
    if (level==2)
        painter.drawPixmap(-100, -60, buff_sprite);
    painter.drawPixmap(-50, -50, 100, 100, t_sprite); //在（-50，-50）画图象
    painter.restore();
}

void Firetower::attackEnemy()
{	// 启动打炮模式
    m_fireRateTimer->start(attack_speed);
}

void Firetower::shootWeapon()
{	// 每次攻击,产生一个子弹
    // 子弹一旦产生,交由m_game管理,进行绘制
    Bullet *bullet = new Bullet(pos, m_chooseEnemy->pos(), attack, m_chooseEnemy, m_game, QPixmap(":/image/fire_bullet.png"));
    bullet->move3();
    m_game->addBullet(bullet);
}

Icetower::Icetower(QPoint pos, GameScene* game, const QPixmap &sprite, const QPixmap &b_sprite)
    :Tower(pos, game, sprite, b_sprite)
{
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

void Icetower::draw(QPainter &painter)//需要传递painter画笔
{
    painter.save();
    // 绘制塔
    painter.translate(pos); // 将pos设置成原点
    if (level==2)
        painter.drawPixmap(-100, -60, buff_sprite);
    painter.drawPixmap(-50, -50, 100, 100, t_sprite); //在（-50，-50）画图象
    painter.restore();
}

void Icetower::attackEnemy()
{	// 启动打炮模式
    m_fireRateTimer->start(attack_speed);
}

void Icetower::shootWeapon()
{	// 每次攻击,产生一个子弹
    // 子弹一旦产生,交由m_game管理,进行绘制
    Bullet *bullet = new Bullet(pos, m_chooseEnemy->pos(), attack, m_chooseEnemy, m_game, QPixmap(":/image/ice_bullet.png"));
    bullet->move2();
    m_game->addBullet(bullet);
}
